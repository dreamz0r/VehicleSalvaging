modded class PlayerBase
{
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
    {
        if (VehicleSalvagingConfigSync.HandleRPC(rpc_type, ctx))
            return;

        super.OnRPC(sender, rpc_type, ctx);
    }

    override void SetActions(out TInputActionMap InputActionMap)
    {
        super.SetActions(InputActionMap);

        AddAction(ActionSalvageSparkPlug, InputActionMap);
        AddAction(ActionSalvageRadiator, InputActionMap);
        AddAction(ActionSalvageBattery, InputActionMap);
        AddAction(ActionSalvageTruckBattery, InputActionMap);
        AddAction(ActionSalvageGlowPlug, InputActionMap);
        AddAction(ActionSalvageHelicopterBattery, InputActionMap);
        AddAction(ActionSalvageHydraulicHoses, InputActionMap);
        AddAction(ActionSalvageIgniterPlug, InputActionMap);
    }
}
