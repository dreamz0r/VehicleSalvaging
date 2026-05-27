////////////////////////////////////////////////////////////////////
//DeRap: config.bin
//Produced from mikero's Dos Tools Dll version 9.98
//https://mikero.bytex.digital/Downloads
//'now' is Wed May 27 10:32:29 2026 : 'file' last modified on Wed May 27 10:14:34 2026
////////////////////////////////////////////////////////////////////

#define _ARMA_

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
