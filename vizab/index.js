
window.addEventListener("load", FPF_Init);

function FPF_Init()
{
        g_FHEM = new FHEM();

        var Div = document.getElementById("WZSofa");
        var oValue = g_FHEM.GetValue("WZ_SofaLampe");
        var Button = new LampButton(Div, oValue);

        Div = document.getElementById("WZKugeln");
        oValue = g_FHEM.GetValue("WZ_Leuchtkugeln");
        Button = new LampButton(Div, oValue);

        Div = document.getElementById("WZHeizung");
        oValue = g_FHEM.GetValue("WZ_Heizung");
        Button = new LampButton(Div, oValue);

        Div = document.getElementById("WZSofaText");
        oValue = g_FHEM.GetValue("WZ_SofaLampe");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0001");
        oValue = g_FHEM.GetValue("airid0001");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0002");
        oValue = g_FHEM.GetValue("airid0002");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0003");
        oValue = g_FHEM.GetValue("airid0003");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0004");
        oValue = g_FHEM.GetValue("airid0004");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0005");
        oValue = g_FHEM.GetValue("airid0005");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0101");
        oValue = g_FHEM.GetValue("airid0101");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0102D");
        oValue = g_FHEM.GetValue("airid0102D");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0102RH");
        oValue = g_FHEM.GetValue("airid0102RH");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0102P");
        oValue = g_FHEM.GetValue("airid0102P");
        Button = new TextValue(Div, oValue);

        Div = document.getElementById("airid0102T");
        oValue = g_FHEM.GetValue("airid0102T");
        Button = new TextValue(Div, oValue);

        setTimeout(UpdateFHEM, 1000);
}


function UpdateFHEM()
{
        g_FHEM.Update ();
        setTimeout(UpdateFHEM, 200);
}


