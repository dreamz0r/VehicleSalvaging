modded class PipeWrench
{
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionSalvageRadiator);
    }
}

modded class Pliers
{
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionSalvageBattery);
        AddAction(ActionSalvageTruckBattery);
    }
}

modded class LugWrench
{
    override void SetActions()
    {
        super.SetActions();

        AddAction(ActionSalvageGlowPlug);
        AddAction(ActionSalvageSparkPlug);
    }
}
