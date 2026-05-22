modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
        actions.Insert(ActionSalvageSparkPlug);
        actions.Insert(ActionSalvageRadiator);
        actions.Insert(ActionSalvageBattery);
        actions.Insert(ActionSalvageTruckBattery);
        actions.Insert(ActionSalvageGlowPlug);
    }
}
