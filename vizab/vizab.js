function ServerConnection()
{
        this.m_HttpReq = new XMLHttpRequest();
        this.m_sMethod = "GET";
        this.m_sUrl = "";
        this.m_bAsync = false;
}

ServerConnection.prototype.Request = function Request()
{
        this.m_HttpReq.open(this.m_sMethod, this.m_sUrl, this.m_bAsync);
        this.m_HttpReq.send();
        if(this.m_bAsync)
        {
                return (true);
        }
        else
        {
                return (this.m_HttpReq.responseText);
        }
}

function FHEM()
{
        this.m_aValues = [];
        this.Update ();
}

FHEM.prototype.SetValue = function SetValue(oValue, sValue)
{
        var Request = new ServerConnection ();
        Request.m_sUrl = "/fhem?cmd=set%20" + oValue.m_sName + "%20" + sValue + "&XHR=1";
        var sResult = Request.Request ();
}

FHEM.prototype.Update = function Update()
{
	try {
        var Request = new ServerConnection ();
        Request.m_sUrl = "/fhem?cmd=jsonlist&XHR=1";
        Request.m_bAsync = false;
        var sValues = Request.Request ();
        var aResultSet = JSON.parse (sValues);
        var aResults = aResultSet["Results"];
        for(var uiListIndex = 0; uiListIndex < aResults.length; uiListIndex++)
        {
                var oList = aResults[uiListIndex];
                var aDevices = oList["devices"];
        for(var uiIndex = 0; uiIndex < aDevices.length; uiIndex++)
        {
                if (!aDevices[uiIndex]) continue;

                var oNewValue = new FHEMValue (aDevices[uiIndex], this);
                var oOldValue = this.GetValue (oNewValue.m_sName);
                if (!oOldValue)
                {
                        this.m_aValues.push (oNewValue);
                        oNewValue.Internal_SendUpdate ();
                        continue;
                }
                var sOld = oOldValue.GetValue ();
                var sNew = oNewValue.GetValue ();
                if (sOld != sNew )
                {
                        oOldValue.Internal_SetValue (oNewValue.GetValue ());
                }
        }
        }
	}
	catch (e) {}
}

FHEM.prototype.GetValue = function GetValue(sName)
{
        for(var uiIndex = 0; uiIndex < this.m_aValues.length; uiIndex++)
        {
                if (!this.m_aValues[uiIndex]) continue;
                if (this.m_aValues[uiIndex].m_sName == sName)
                {
                        return this.m_aValues[uiIndex];
                }
        }
}

function FHEMValue (oValue, oFHEM)
{
        this.m_oFHEM = oFHEM;
        this.m_sName = oValue["NAME"];
        this.m_sValue = oValue["STATE"];
        this.m_aRegisteredOnChange = [];
}

FHEMValue.prototype.Internal_SetValue = function Internal_SetValue(sValue)
{
        this.m_sValue = sValue;
        this.Internal_SendUpdate ();
};

FHEMValue.prototype.Internal_SendUpdate = function Internal_SendUpdate (sValue)
{
        for(var uiIndex in this.m_aRegisteredOnChange)
        {
                var o = this.m_aRegisteredOnChange[uiIndex];
                if (o && o.OnValueChanged)
                {
                        o.OnValueChanged (this);
                }
        }
}

FHEMValue.prototype.Register = function Register(oObject)
{
        this.m_aRegisteredOnChange.push(oObject);
        this.Internal_SendUpdate ();
}

FHEMValue.prototype.GetValue = function GetValue()
{
        return this.m_sValue;
}

FHEMValue.prototype.SetValue = function SetValue(sValue)
{
        return this.m_oFHEM.SetValue(this, sValue);
}

var g_FHEM = null;

/*****************************************************************************************/

function Vizab_OnClick(e)
{
        var oObject = e.currentTarget.oObject;
        if(oObject && oObject.OnClick)
        {
                oObject.OnClick();
        }
}

function LampButton(Div, oValue)
{
        this.m_Div = Div;
        this.m_oValue = oValue;

        Div.onclick = Vizab_OnClick;
        Div.oObject = this;
        oValue.Register (this);
}

LampButton.prototype.OnClick = function OnClick()
{
        if ( this.m_oValue.GetValue() == "on")
        {
                this.m_oValue.SetValue("off");
        }
        else
        {
                this.m_oValue.SetValue("on");
        }
}

LampButton.prototype.OnValueChanged = function OnValueChanged(oValue)
{
        var sValue = oValue.GetValue();
        var iValue = parseInt(sValue);
        if(!isFinite(iValue))
        {
                this.m_Div.src = "/fhem/icons/" + sValue + ".png";
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
                this.m_Div.src = "/fhem/icons/" + sValue + ".png";
        }
}

function TextValue(Div, oValue)
{
        this.m_Div = Div;
        this.m_oValue = oValue;
//	Div.disabled = "disabled";

        oValue.Register (this);
}

TextValue.prototype.OnValueChanged = function OnValueChanged(oValue)
{
        var sValue = oValue.GetValue();
	var sAtt = this.m_Div.getAttribute("unit");
        this.m_Div.value = sValue ? ( sValue + (sAtt ?  " " + sAtt : "" ) ) : "???" ;
}

