unit ProcessUtils; 

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Process, AsyncProcess, FileUtil
  {$IFDEF MSWINDOWS}
  ,Windows
  {$ENDIF}
  ;

type
  TLineWriteEvent = procedure(Line : string) of object;
  TCharWriteEvent = procedure(c : char) of object;

  { TExtendedProcess }

  TExtendedProcess = class(TThread)
  private
    FActive: Boolean;
    FOnBlockWritten: TLineWriteEvent;
    FOnCharWritten: TCharWriteEvent;
    FOnDone: TNotifyEvent;
    FOnLineWritten: TLineWriteEvent;
    FProcess : TProcessUTF8;
    FBytesRead : Integer;
    FBuffer : string;
    FDataLine : string;
    FDataChar : char;
    FDataBlock : string;
    procedure Datafound;
    procedure Datacharfound;
    procedure BlockDatafound;
    procedure DoDone;
    function GetEnvironmentUTF8: TStrings;
    function GetExistStatus: Integer;
    procedure SetEnvironmentUTF8(const AValue: TStrings);
  protected
    procedure   Execute;override;
  public
    constructor Create(Cmdln : string;Autorun : Boolean = True;Dir : string = '');
    property    OnLineWritten : TLineWriteEvent read FOnLineWritten write FOnLineWritten;
    property    OnCharWritten : TCharWriteEvent read FOnCharWritten write FOnCharWritten;
    property    OnBlockWritten : TLineWriteEvent read FOnBlockWritten write FOnBlockWritten;
    procedure   Writeln(str : string);
    property    OnDone : TNotifyEvent read FOnDone write FOnDone;
    property    Active : Boolean read FActive;
    property    ExitStatus : Integer read GetExistStatus;
    property    Environment: TStrings read GetEnvironmentUTF8 write SetEnvironmentUTF8;
    procedure   Start;
  end;

procedure ExecProcess(CommandLine : string;CurDir : string = '';Waitfor : Boolean = True);
procedure ExecVisualProcess(CommandLine : string;CurDir : string = '';Waitfor : Boolean = True);
function ExecProcessEx(CommandLine : string;CurDir : string = '') : string;

implementation

{ TExtendedProcess }

procedure TExtendedProcess.Datafound;
begin
  if Assigned(FOnLineWritten) then
    FOnLineWritten(SysToUTF8(FDataLine));
end;

procedure TExtendedProcess.Datacharfound;
begin
  if Assigned(FOnCharWritten) then
    FOnCharWritten(FDataChar);
end;

procedure TExtendedProcess.BlockDatafound;
begin
  if Assigned(FOnBlockWritten) then
    FOnBlockWritten(SysToUTF8(FDataBlock));
end;

procedure TExtendedProcess.DoDone;
begin
  FActive := False;
  if Assigned(FOnDone) then
    FOnDone(Self);
end;

function TExtendedProcess.GetEnvironmentUTF8: TStrings;
begin
  Result := FProcess.Environment;
end;

function TExtendedProcess.GetExistStatus: Integer;
begin
  if Assigned(FProcess) then
    Result := FProcess.ExitStatus
  else Result := -1;
end;

procedure TExtendedProcess.SetEnvironmentUTF8(const AValue: TStrings);
begin
  FProcess.Environment.Assign(AValue);
end;

constructor TExtendedProcess.Create(Cmdln: string;Autorun : Boolean;Dir: string);
begin
  FActive := False;
  FBuffer := '';
  FProcess := TProcessUTF8.Create(nil);
  FProcess.Options:= [poUsePipes, poNoConsole, poStdErrToOutPut,poDefaultErrorMode, poNewProcessGroup];
  FProcess.ShowWindow := swoNone;
  FProcess.CommandLine := Cmdln;
  FreeOnTerminate := True;
  if Dir <> '' then
    FProcess.CurrentDirectory := Dir;
  if Autorun then
    begin
      try
        FProcess.Execute;
        FActive := True;
      except
        FActive := False;
        try
          FreeAndNil(FProcess);
        except
          FProcess := nil;
        end;
        DoDone;
        exit;
      end;
      inherited Create(False);
    end
  else
    begin
      inherited Create(True);
    end;
end;

procedure TExtendedProcess.Execute;
const
  READ_BYTES = 10;
var
  tmp : string;
  i: Integer;
begin
  while (not Terminated) do
    begin
      setlength(tmp,FProcess.Output.NumBytesAvailable);
      if length(tmp) > 0 then
        setlength(tmp,FProcess.Output.Read(tmp[1], length(tmp)));
      if (tmp = '') then
        begin
          if FProcess.Running then
            sleep(100)
          else
            break;
        end
      else
        begin
          for i := 1 to length(tmp) do
            begin
              FDataChar := tmp[i];
              Synchronize(@datacharfound);
            end;
          FDataBlock := tmp;
          Synchronize(@blockdatafound);
          tmp := stringreplace(tmp,#13,'',[rfReplaceAll]);
          while pos(#10,tmp) > 0 do
            begin
              FDataLine := FDataLine+copy(tmp,0,pos(#10,tmp)-1);
              tmp := copy(tmp,pos(#10,tmp)+1,length(tmp));
              Synchronize(@datafound);
              FDataLine := '';
            end;
          FDataLine := FDataLine+tmp;
        end;
    end;
  if fDataLine <> '' then
    Synchronize(@datafound);
  FProcess.Free;
  Synchronize(@DoDone);
end;

procedure TExtendedProcess.Writeln(str: string);
var
  tmp : string;
begin
  FProcess.Input.Write(str[1],length(str));
  tmp := #10;
  FProcess.Input.Write(tmp[1],1);
end;

procedure TExtendedProcess.Start;
begin
  if FProcess.Active then exit;
  FActive := True;
  FProcess.Execute;
  Resume;
end;

function ExecProcessEx(CommandLine : string;CurDir : string = '') : string;
const
  READ_BYTES = 2048;
var
  process : TProcessUTF8;
  tmps: tstringlist;
  err : string;
begin
  Process := TProcessUTF8.Create(nil);
//  Process.Options := [poUsePipes];
  Process.Options:= [poUsePipes, poWaitOnExit, poNoConsole, poStdErrToOutPut, poNewProcessGroup];
//  Process.ShowWindow := swoHide;
  Process.CommandLine := CommandLine;
  if CurDir <> '' then
    Process.CurrentDirectory := CurDir;
  try
    Process.Execute;
  except
    on e : exception do
      err := err+#13+e.Message;
  end;
  tmps := TStringList.Create;
  tmps.LoadFromStream(Process.Output);
  Process.Free;
  Result := tmps.Text;
  tmps.Free;
  if err <> '' then
    Result := 'errors:'+err+#13+Result;
end;

procedure ExecProcess(CommandLine : string;CurDir : string = '';Waitfor : Boolean = True);
var
{$IFDEF MSWINDOWS}
  SUInfo: TStartupInfo;
  ProcInfo: TProcessInformation;
  CmdLine: string;
  Res: Boolean;
{$ELSE}
  process : TProcessUTF8;
{$ENDIF}
begin
{$IFDEF MSWINDOWS}
  FillChar(SUInfo, SizeOf(SUInfo), #0);
  with SUInfo do begin
    cb := SizeOf(SUInfo);
    dwFlags := STARTF_USESHOWWINDOW;
    wShowWindow := SW_HIDE
  end;
  Res := CreateProcess(NIL, PChar(CommandLine), NIL, NIL, FALSE,
                          CREATE_NEW_CONSOLE or
                          NORMAL_PRIORITY_CLASS, NIL,
                          PChar(CurDir),
                          SUInfo, ProcInfo);
  { Wait for it to finish. }
  if Res and Waitfor then
    WaitForSingleObject(ProcInfo.hProcess, INFINITE);
{$ELSE}
  Process := TProcessUTF8.Create(nil);
  if CurDir <> '' then
    Process.CurrentDirectory := CurDir;
  Process.CommandLine := CommandLine;
  if Waitfor then
    Process.Options := [poNewConsole{poNoConsole},poWaitOnExit]
  else
    Process.Options := [poNewConsole{poNoConsole}];
//  Process.ShowWindow := swoHide;
  Process.Execute;
  if Waitfor then Process.Free;
{$ENDIF}
end;

procedure ExecVisualProcess(CommandLine : string;CurDir : string = '';Waitfor : Boolean = True);
var
  process : TProcessUTF8;
begin
  Process := TProcessUTF8.Create(nil);
  if CurDir <> '' then
    Process.CurrentDirectory := CurDir;
  Process.CommandLine := CommandLine;
  if Waitfor then
    Process.Options := [poWaitOnExit]
  else
    Process.Options := [];
  Process.Execute;
  if Waitfor then Process.Free;
end;


end.

