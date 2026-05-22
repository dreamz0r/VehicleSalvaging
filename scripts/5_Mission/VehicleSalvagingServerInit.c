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
}
