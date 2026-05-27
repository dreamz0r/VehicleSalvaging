class VehicleSalvagingServerInit
{
    static void EnsureProfileFiles()
    {
        VehicleSalvagingConfig.Get();
        VehicleSalvagingWreckConfig.Get();
        VehicleSalvagingCooldownManager.GetInstance().ClearCooldowns();
    }
}

modded class MissionServer
{
    override void OnInit()
    {
        super.OnInit();
        VehicleSalvagingServerInit.EnsureProfileFiles();
    }

    override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
    {
        super.InvokeOnConnect(player, identity);
        VehicleSalvagingConfigSync.SendToClient(player, identity);
    }
}
