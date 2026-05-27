class VehicleSalvagingWrecks
{
    static bool IsSparkPlugWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().SparkPlugWrecks, objType);
    }

    static bool IsCarBatteryWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().CarBatteryWrecks, objType);
    }

    static bool IsRadiatorWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().RadiatorWrecks, objType);
    }

    static bool IsGlowPlugWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().GlowPlugWrecks, objType);
    }

    static bool IsTruckBatteryWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().TruckBatteryWrecks, objType);
    }

    static bool IsHelicopterBatteryWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().HelicopterBatteryWrecks, objType);
    }

    static bool IsHydraulicHosesWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().HydraulicHosesWrecks, objType);
    }

    static bool IsIgniterPlugWreck(string objType)
    {
        return WreckListContains(VehicleSalvagingWreckConfig.Get().IgniterPlugWrecks, objType);
    }

    protected static bool WreckListContains(array<string> wrecks, string objType)
    {
        if (!wrecks || objType == "")
            return false;

        objType.ToLower();

        for (int i = 0; i < wrecks.Count(); i++)
        {
            if (wrecks.Get(i) == objType)
                return true;
        }

        return false;
    }
}
