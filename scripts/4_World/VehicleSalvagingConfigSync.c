const int VEHICLE_SALVAGING_RPC_CONFIG_SYNC = 58942101;
const int VEHICLE_SALVAGING_RPC_WRECK_CONFIG_SYNC = 58942102;

class VehicleSalvagingConfigSync
{
    static void SendToClient(PlayerBase player, PlayerIdentity identity)
    {
        if (!GetGame().IsServer() || !player || !identity)
            return;

        Param1<ref VehicleSalvagingConfigData> configParam = new Param1<ref VehicleSalvagingConfigData>(VehicleSalvagingConfig.Get());
        GetGame().RPCSingleParam(player, VEHICLE_SALVAGING_RPC_CONFIG_SYNC, configParam, true, identity);

        Param1<ref VehicleSalvagingWreckConfigData> wreckConfigParam = new Param1<ref VehicleSalvagingWreckConfigData>(VehicleSalvagingWreckConfig.Get());
        GetGame().RPCSingleParam(player, VEHICLE_SALVAGING_RPC_WRECK_CONFIG_SYNC, wreckConfigParam, true, identity);
    }

    static bool HandleRPC(int rpcType, ParamsReadContext ctx)
    {
        if (rpcType == VEHICLE_SALVAGING_RPC_CONFIG_SYNC)
        {
            Param1<ref VehicleSalvagingConfigData> configParam = new Param1<ref VehicleSalvagingConfigData>(null);

            if (ctx.Read(configParam))
                VehicleSalvagingConfig.Set(configParam.param1);

            return true;
        }

        if (rpcType == VEHICLE_SALVAGING_RPC_WRECK_CONFIG_SYNC)
        {
            Param1<ref VehicleSalvagingWreckConfigData> wreckConfigParam = new Param1<ref VehicleSalvagingWreckConfigData>(null);

            if (ctx.Read(wreckConfigParam))
                VehicleSalvagingWreckConfig.Set(wreckConfigParam.param1);

            return true;
        }

        return false;
    }
}
