// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

function ServerConnection ()
{
  this.m_HttpReq = new XMLHttpRequest();
  this.m_sMethod = "GET";
  this.m_sUrl = "";
  this.m_bAsync = false;
  this.m_Target = null;
}

ServerConnection.prototype.Request = function Request ()
{
  this.m_HttpReq.open(this.m_sMethod, this.m_sUrl, this.m_bAsync);

  this.m_HttpReq.onreadystatechange = Vizab_OnReadyStateChange;
  this.m_HttpReq.m_oObj = this;

  this.m_HttpReq.send();

  if (this.m_bAsync)
  {
    return (true);
  }
  else
  {
    return (this.m_HttpReq.responseText);
  }
};

ServerConnection.prototype.OnReadyStateChanged = function OnReadyStateChanged ()
{
  switch (this.m_HttpReq.readyState)
  {
  case 4:
    if (this.m_Target)
    {
      if (this.m_HttpReq.status == 0)
      {
        //
      }
      else
      {
        this.m_Target.OnReady(this, this.m_HttpReq.responseText);
      }
    }
    break;
  }
};

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

var g_aJSObjects = [];
var g_uiJSObjectCounter = 0;

function RegisterObject(oObj)
{
  g_aJSObjects[g_uiJSObjectCounter] = oObj;
  oObj.m_uiJSObjectIndex = g_uiJSObjectCounter;
  g_uiJSObjectCounter++;
}

function TimeoutObject(uiJSObjectIndex, sFunction)
{
  var oObj = g_aJSObjects[uiJSObjectIndex];
  if (oObj && oObj[sFunction])
  {
    oObj[sFunction]();
  }
}

function DoTimeout(oObj, sFunction, uiTimeout)
{
  console.log("DoTimeout sFunction=" + sFunction + ", uiTimeout=" + uiTimeout);
  return setTimeout("TimeoutObject(" + oObj.m_uiJSObjectIndex + ",'" + sFunction + "');", uiTimeout);
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

function FHEM ()
{
  console.log("FHEM.construct");
  RegisterObject(this);
  this.m_aValues = [];
  this.m_bValuesLoaded = false;
  this.Update(true);
  this.Inform ();
}

FHEM.prototype.OnTimeoutUpdate = function OnTimeoutUpdate ()
{
  console.log("FHEM.OnTimeoutUpdate");
  this.Update (true);
};

FHEM.prototype.SetValue = function SetValue (oValue, sValue)
{
  console.log("FHEM.SetValue");
  var Request = new ServerConnection();
  Request.m_sUrl = "/fhem?cmd=set%20" + oValue.m_sName + "%20" + sValue + "&XHR=1";
  Request.m_bAsync = true;
  Request.Request();
};

FHEM.prototype.Update = function Update (bRestartTimeout)
{
  console.log("FHEM.Update, bRestartTimeout=" + bRestartTimeout);
  var Request = new ServerConnection();
  Request.m_sUrl = "/fhem?cmd=jsonlist&XHR=1";
  Request.m_bAsync = true;
  Request.m_Target = this;
  Request.m_sType = "jsonlist";
  Request.m_bRestartTimeout = (bRestartTimeout == true);
  Request.Request();
};

FHEM.prototype.Inform = function Inform ()
{
  console.log("FHEM.Inform");
  var Request = new ServerConnection();
  Request.m_sUrl = "/fhem?room=all&inform=on";
  Request.m_bAsync = true;
  Request.m_Target = this;
  Request.m_sType = "inform";
  Request.Request();
};

FHEM.prototype.OnReady = function OnReady (Request, sResult)
{
  switch (Request.m_sType)
  {
  case "inform":
    console.log("FHEM.OnReady inform");
    this.Update (false);
    this.Inform ();
    break;
  case "jsonlist":
    console.log("FHEM.OnReady jsonlist");
    var bOk = false;
    try
    {
      var aResultSet = JSON.parse(sResult);
  
      var aResults = aResultSet["Results"];
      for ( var uiListIndex = 0; uiListIndex < aResults.length; uiListIndex++)
      {
        var oList = aResults[uiListIndex];
        var aDevices = oList["devices"];
        for ( var uiIndex = 0; uiIndex < aDevices.length; uiIndex++)
        {
          if (!aDevices[uiIndex])
            continue;
  
          var oNewValue = new FHEMValue(aDevices[uiIndex], this);
          var oOldValue = this.GetValue(oNewValue.m_sName);
          if (!oOldValue)
          {
            this.m_aValues.push(oNewValue);
            oNewValue.Internal_SendUpdate();
            continue;
          }
          var sOld = oOldValue.GetValue();
          var sNew = oNewValue.GetValue();
          if (sOld != sNew)
          {
            oOldValue.Internal_SetValue(oNewValue.GetValue());
          }
        }
      }
  
      bOk = true;
    }
    catch (e)
    {
      //
    }
  
    if (bOk && !this.m_bValuesLoaded)
    {
      this.m_oObj.OnValuesLoaded(this);
      this.m_bValuesLoaded = true;
    }
    this.m_oObj.OnValuesUpdated(this);
    
    if (  Request.m_bRestartTimeout )
    {
      this.m_tTimeoutUpdate = DoTimeout(this, "OnTimeoutUpdate", 20000);
    }
    break;
  }
};

FHEM.prototype.GetValue = function GetValue (sName)
{
  for ( var uiIndex = 0; uiIndex < this.m_aValues.length; uiIndex++)
  {
    if (!this.m_aValues[uiIndex])
      continue;
    if (this.m_aValues[uiIndex].m_sName == sName)
    {
      return this.m_aValues[uiIndex];
    }
  }
  var oNewValue = new FHEMValue({
    NAME : sName,
    STATE : "???"
  }, this);
  this.m_aValues.push(oNewValue);
  return (oNewValue);
};

// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

function FHEMValue (oValue, oFHEM)
{
  this.m_oFHEM = oFHEM;
  this.m_sName = oValue["NAME"];
  this.m_sValue = oValue["STATE"];
  this.m_aRegisteredOnChange = [];
}

FHEMValue.prototype.Internal_SetValue = function Internal_SetValue (sValue)
{
  this.m_sValue = sValue;
  this.Internal_SendUpdate();
};

FHEMValue.prototype.Internal_SendUpdate = function Internal_SendUpdate (sValue)
{
  for ( var uiIndex in this.m_aRegisteredOnChange)
  {
    var o = this.m_aRegisteredOnChange[uiIndex];
    if (o && o.OnValueChanged)
    {
      o.OnValueChanged(this);
    }
  }
};

FHEMValue.prototype.Register = function Register (oObject)
{
  this.m_aRegisteredOnChange.push(oObject);
  this.Internal_SendUpdate();
};

FHEMValue.prototype.GetValue = function GetValue ()
{
  return this.m_sValue;
};

FHEMValue.prototype.SetValue = function SetValue (sValue)
{
  return this.m_oFHEM.SetValue(this, sValue);
};

// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

function LampButton (Div, oValue)
{
  this.m_Div = Div;
  this.m_oValue = oValue;
  this.m_bDimmable = false;

  Div.onclick = Vizab_OnClick;
  Div.onmousedown = Vizab_OnMouseDown;
  Div.oObject = this;
  oValue.Register(this);
}

LampButton.prototype.OnMouseDown = function OnMouseDown (Event)
{
  if ((Event.button == 2) && (this.m_bDimmable))
  {
    Event.stopPropagation();
    var sValue = prompt("Enter new dim value:", "50%");
    var iValue = parseInt(sValue, 10);
    if (isFinite(iValue))
    {
      this.m_oValue.SetValue(iValue + "%");
    }
    return (false);
  }
};

LampButton.prototype.OnClick = function OnClick (Event)
{
  if (this.m_oValue.GetValue() == "off")
  {
    this.m_oValue.SetValue("on");
  }
  else
  {
    this.m_oValue.SetValue("off");
  }
};

LampButton.prototype.OnValueChanged = function OnValueChanged (oValue)
{
  var sValue = oValue.GetValue();
  var iValue = parseInt(sValue);
  if (!isFinite(iValue))
  {
    switch (sValue)
    {
    case "on":
    case "off":
      this.m_Div.src = "png/" + sValue + ".png";
      break;

    case "MISSING ACK":
    default:
      this.m_Div.src = "png/error.png";
      break;
    }
  }
  else
  {
    if (iValue < 0)
    {
      sValue = "off";
    }
    else if (iValue < 9)
    {
      sValue = "dim06";
    }
    else if (iValue < 15)
    {
      sValue = "dim12";
    }
    else if (iValue < 21)
    {
      sValue = "dim18";
    }
    else if (iValue < 28)
    {
      sValue = "dim25";
    }
    else if (iValue < 34)
    {
      sValue = "dim31";
    }
    else if (iValue < 40)
    {
      sValue = "dim37";
    }
    else if (iValue < 46)
    {
      sValue = "dim43";
    }
    else if (iValue < 53)
    {
      sValue = "dim50";
    }
    else if (iValue < 59)
    {
      sValue = "dim56";
    }
    else if (iValue < 65)
    {
      sValue = "dim62";
    }
    else if (iValue < 71)
    {
      sValue = "dim68";
    }
    else if (iValue < 78)
    {
      sValue = "dim75";
    }
    else if (iValue < 84)
    {
      sValue = "dim81";
    }
    else if (iValue < 90)
    {
      sValue = "dim87";
    }
    else if (iValue < 96)
    {
      sValue = "dim93";
    }
    else
    {
      sValue = "on";
    }
    this.m_Div.src = "png/" + sValue + ".png";
  }
};

// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

function TextValue (Div, oValue)
{
  this.m_Div = Div;
  Div.onclick = Vizab_OnClick;
  Div.oObject = this;
  this.m_oValue = oValue;
  // Div.disabled = "disabled";
  this.m_bReadOnly = true;

  oValue.Register(this);
}

TextValue.prototype.OnValueChanged = function OnValueChanged (oValue)
{
  var sValue = oValue.GetValue();
  var sAtt = this.m_Div.getAttribute("unit");
  this.m_Div.value = sValue ? (sValue + (sAtt ? " " + sAtt : "")) : "???";
};

TextValue.prototype.OnClick = function TextValue_OnClick (Event)
{
  if (this.m_bReadOnly)
  {
    return (false);
  }
  var sValue = prompt("Enter new value (on|off|50%):", "");
  if(sValue)
  {
    this.m_oValue.SetValue(sValue);
  }
};

// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------

function Vizab_OnReadyStateChange (e)
{
  var oObj = this.m_oObj;
  if (oObj && oObj.OnReadyStateChanged)
  {
    oObj.OnReadyStateChanged();
  }
}

function Vizab_OnMouseDown (e)
{
  var oObject = e.currentTarget.oObject;
  if (oObject && oObject.OnMouseDown)
  {
    oObject.OnMouseDown(e);
  }
  return (false);
}

function Vizab_OnClick (e)
{
  var oObject = e.currentTarget.oObject;
  if (oObject && oObject.OnClick)
  {
    oObject.OnClick(e);
  }
  return (false);
}
