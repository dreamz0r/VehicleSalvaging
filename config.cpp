class CfgPatches
{
    class VehicleSalvaging
    {
        units[] = {};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data","DZ_Scripts","DZ_Gear_Tools","DZ_Vehicles_Parts"};
    };
};

class CfgMods
{
    class VehicleSalvaging
    {
        dir = "VehicleSalvaging";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        name = "Vehicle Salvaging";
        credits = "Griffin";
        author = "Griffin";
        authorID = "0";
        version = "1.0";

        type = "mod";

        dependencies[] = {"World","Mission"};

        class defs
        {
            class worldScriptModule
            {
                value = "";
                files[] = {"VehicleSalvaging/scripts/4_World"};
            };

            class missionScriptModule
            {
                value = "";
                files[] = {"VehicleSalvaging/scripts/5_Mission"};
            };
        };
    };
};
