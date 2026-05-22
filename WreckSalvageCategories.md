# ChernarusPlus Wreck Salvage Categories

This file is the readable source list for deciding which ChernarusPlus wrecks belong in each salvage category.

Verified against local DayZ ChernarusPlus CE files:

- `P:\DZ\worlds\chernarusplus\ce\mapgroupproto.xml`
- `P:\DZ\worlds\chernarusplus\ce\mapgrouppos.xml`
- `P:\DZ\worlds\chernarusplus\ce\cfgeventgroups.xml`

Default script config lives in:

```text
scripts/4_World/VehicleSalvagingWreckConfig.c
```

Server owners can edit the generated runtime file instead of changing scripts:

```text
$profile:VehicleSalvaging/VehicleSalvagingWreckConfig.json
```

The scripts lowercase the target classname before comparing it, so these reference names are written as lowercase `case` lines.

## Passenger Gasoline

Recommended salvage:

- `SparkPlug`
- `CarBattery`
- `CarRadiator`

```c
case "land_wreck_hb01_aban1_blue":        // Passenger gasoline hatchback, blue.
case "land_wreck_hb01_aban1_blue_de":     // Passenger gasoline hatchback, blue dynamic-event wreck.
case "land_wreck_hb01_aban1_green":       // Passenger gasoline hatchback, green.
case "land_wreck_hb01_aban1_green_de":    // Passenger gasoline hatchback, green dynamic-event wreck.
case "land_wreck_hb01_aban1_white":       // Passenger gasoline hatchback, white.
case "land_wreck_hb01_aban1_white_de":    // Passenger gasoline hatchback, white dynamic-event wreck.
case "land_wreck_hb01_aban2_blue":        // Passenger gasoline hatchback alternate damage layout, blue.
case "land_wreck_hb01_aban2_blue_de":     // Passenger gasoline hatchback alternate damage layout, blue dynamic-event wreck.
case "land_wreck_hb01_aban2_green":       // Passenger gasoline hatchback alternate damage layout, green.
case "land_wreck_hb01_aban2_green_de":    // Passenger gasoline hatchback alternate damage layout, green dynamic-event wreck.
case "land_wreck_hb01_aban2_white":       // Passenger gasoline hatchback alternate damage layout, white.
case "land_wreck_hb01_aban2_white_de":    // Passenger gasoline hatchback alternate damage layout, white dynamic-event wreck.
case "land_wreck_hb02_aban1_black":       // Passenger gasoline hatchback, black.
case "land_wreck_hb02_aban1_black_de":    // Passenger gasoline hatchback, black dynamic-event wreck.
case "land_wreck_hb02_aban1_blue":        // Passenger gasoline hatchback, blue.
case "land_wreck_hb02_aban1_blue_de":     // Passenger gasoline hatchback, blue dynamic-event wreck.
case "land_wreck_hb02_aban1_red":         // Passenger gasoline hatchback, red.
case "land_wreck_hb02_aban1_red_de":      // Passenger gasoline hatchback, red dynamic-event wreck.
case "land_wreck_hb02_aban2_black":       // Passenger gasoline hatchback alternate damage layout, black.
case "land_wreck_hb02_aban2_black_de":    // Passenger gasoline hatchback alternate damage layout, black dynamic-event wreck.
case "land_wreck_hb02_aban2_blue":        // Passenger gasoline hatchback alternate damage layout, blue.
case "land_wreck_hb02_aban2_blue_de":     // Passenger gasoline hatchback alternate damage layout, blue dynamic-event wreck.
case "land_wreck_hb02_aban2_red":         // Passenger gasoline hatchback alternate damage layout, red.
case "land_wreck_hb02_aban2_red_de":      // Passenger gasoline hatchback alternate damage layout, red dynamic-event wreck.
case "land_wreck_lada_green":             // Passenger gasoline Lada wreck, green.
case "land_wreck_lada_red":               // Passenger gasoline Lada wreck, red.
case "land_wreck_s1023_beige":            // Passenger gasoline S1023 van/minibus wreck, beige.
case "land_wreck_s1023_blue":             // Passenger gasoline S1023 van/minibus wreck, blue.
case "land_wreck_s1023_medic_beige_de":   // Passenger gasoline S1023 medical dynamic-event wreck.
case "land_wreck_s1023_red":              // Passenger gasoline S1023 van/minibus wreck, red.
case "land_wreck_sed01_aban1_black":      // Passenger gasoline sedan, black.
case "land_wreck_sed01_aban1_black_de":   // Passenger gasoline sedan, black dynamic-event wreck.
case "land_wreck_sed01_aban1_white":      // Passenger gasoline sedan, white.
case "land_wreck_sed01_aban1_white_de":   // Passenger gasoline sedan, white dynamic-event wreck.
case "land_wreck_sed01_aban1_wine":       // Passenger gasoline sedan, wine.
case "land_wreck_sed01_aban1_wine_de":    // Passenger gasoline sedan, wine dynamic-event wreck.
case "land_wreck_sed01_aban2_black":      // Passenger gasoline sedan alternate damage layout, black.
case "land_wreck_sed01_aban2_black_de":   // Passenger gasoline sedan alternate damage layout, black dynamic-event wreck.
case "land_wreck_sed01_aban2_white":      // Passenger gasoline sedan alternate damage layout, white.
case "land_wreck_sed01_aban2_white_de":   // Passenger gasoline sedan alternate damage layout, white dynamic-event wreck.
case "land_wreck_sed01_aban2_wine":       // Passenger gasoline sedan alternate damage layout, wine.
case "land_wreck_sed01_aban2_wine_de":    // Passenger gasoline sedan alternate damage layout, wine dynamic-event wreck.
case "land_wreck_sed02_aban1_grey":       // Passenger gasoline sedan, grey.
case "land_wreck_sed02_aban1_grey_de":    // Passenger gasoline sedan, grey dynamic-event wreck.
case "land_wreck_sed02_aban1_red":        // Passenger gasoline sedan, red.
case "land_wreck_sed02_aban1_red_de":     // Passenger gasoline sedan, red dynamic-event wreck.
case "land_wreck_sed02_aban1_yellow":     // Passenger gasoline sedan, yellow.
case "land_wreck_sed02_aban1_yellow_de":  // Passenger gasoline sedan, yellow dynamic-event wreck.
case "land_wreck_sed02_aban2_grey":       // Passenger gasoline sedan alternate damage layout, grey.
case "land_wreck_sed02_aban2_grey_de":    // Passenger gasoline sedan alternate damage layout, grey dynamic-event wreck.
case "land_wreck_sed02_aban2_red":        // Passenger gasoline sedan alternate damage layout, red.
case "land_wreck_sed02_aban2_red_de":     // Passenger gasoline sedan alternate damage layout, red dynamic-event wreck.
case "land_wreck_sed02_aban2_yellow":     // Passenger gasoline sedan alternate damage layout, yellow.
case "land_wreck_sed02_aban2_yellow_de":  // Passenger gasoline sedan alternate damage layout, yellow dynamic-event wreck.
case "land_wreck_volha_blue":             // Passenger gasoline Volha/Olga wreck, blue.
case "land_wreck_volha_grey":             // Passenger gasoline Volha/Olga wreck, grey.
```

## Police Gasoline

Recommended salvage:

- `SparkPlug`
- `CarBattery`
- `CarRadiator`

```c
case "land_wreck_hb01_aban1_police_de":   // Police gasoline hatchback dynamic-event wreck.
case "land_wreck_hb01_aban2_police_de":   // Police gasoline hatchback alternate dynamic-event wreck.
case "land_wreck_sed01_aban1_police":     // Police gasoline sedan wreck.
case "land_wreck_sed01_aban1_police_de":  // Police gasoline sedan dynamic-event wreck.
case "land_wreck_sed01_aban2_police":     // Police gasoline sedan alternate damage layout.
case "land_wreck_sed01_aban2_police_de":  // Police gasoline sedan alternate dynamic-event wreck.
case "land_wreck_volha_police":           // Police gasoline Volha/Olga patrol wreck.
```

## Light Diesel

Recommended salvage:

- `CarBattery`
- `CarRadiator`
- `GlowPlug`

```c
case "land_wreck_offroad02_aban1":     // Light military diesel M1025/offroad wreck.
case "land_wreck_offroad02_aban1_de":  // Light military diesel M1025/offroad dynamic-event wreck.
case "land_wreck_offroad02_aban2":     // Light military diesel M1025/offroad alternate damage layout.
case "land_wreck_offroad02_aban2_de":  // Light military diesel M1025/offroad alternate dynamic-event wreck.
```

## Light Van Diesel

Recommended salvage:

- `CarBattery`
- `CarRadiator`
- `GlowPlug`

```c
case "land_wreck_van01_aban1_beige":  // Light commercial van wreck, beige.
case "land_wreck_van01_aban1_blue":   // Light commercial van wreck, blue.
case "land_wreck_van01_aban2_beige":  // Light commercial van alternate damage layout, beige.
case "land_wreck_van01_aban2_blue":   // Light commercial van alternate damage layout, blue.
```

## Heavy Diesel

Recommended salvage:

- `TruckBattery`
- `CarRadiator`
- `GlowPlug`

```c
case "land_wreck_ikarus":                      // Heavy diesel bus wreck.
case "land_wreck_ikarus_de":                   // Heavy diesel bus dynamic-event wreck.
case "land_wreck_tractor_de":                  // Farming diesel tractor dynamic-event wreck.
case "land_wreck_truck01_aban1_blue":          // Heavy diesel truck wreck, blue.
case "land_wreck_truck01_aban1_blue_de":       // Heavy diesel truck dynamic-event wreck, blue.
case "land_wreck_truck01_aban1_firetruck":     // Heavy diesel firetruck wreck.
case "land_wreck_truck01_aban1_firetruck_de":  // Heavy diesel firetruck dynamic-event wreck.
case "land_wreck_truck01_aban1_green":         // Heavy diesel truck wreck, green.
case "land_wreck_truck01_aban1_green_de":      // Heavy diesel truck dynamic-event wreck, green.
case "land_wreck_truck01_aban1_orange":        // Heavy diesel truck wreck, orange.
case "land_wreck_truck01_aban1_orange_de":     // Heavy diesel truck dynamic-event wreck, orange.
case "land_wreck_truck01_aban2_blue":          // Heavy diesel truck alternate damage layout, blue.
case "land_wreck_truck01_aban2_blue_de":       // Heavy diesel truck alternate dynamic-event wreck, blue.
case "land_wreck_truck01_aban2_firetruck":     // Heavy diesel firetruck alternate damage layout.
case "land_wreck_truck01_aban2_firetruck_de":  // Heavy diesel firetruck alternate dynamic-event wreck.
case "land_wreck_truck01_aban2_green":         // Heavy diesel truck alternate damage layout, green.
case "land_wreck_truck01_aban2_green_de":      // Heavy diesel truck alternate dynamic-event wreck, green.
case "land_wreck_truck01_aban2_orange":        // Heavy diesel truck alternate damage layout, orange.
case "land_wreck_truck01_aban2_orange_de":     // Heavy diesel truck alternate dynamic-event wreck, orange.
case "land_wreck_truck02_aban1_green":         // Heavy diesel truck02 wreck, green.
case "land_wreck_truck02_aban1_orange":        // Heavy diesel truck02 wreck, orange.
case "land_wreck_truck02_aban2_green":         // Heavy diesel truck02 alternate damage layout, green.
case "land_wreck_truck02_aban2_orange":        // Heavy diesel truck02 alternate damage layout, orange.
case "land_wreck_v3s_de":                      // Heavy diesel V3S dynamic-event wreck.
```

## ChernarusPlus Wrecks Intentionally Excluded

These exist in ChernarusPlus data but do not currently produce vehicle parts:

```c
case "land_wreck_c130j":              // Aircraft wreck.
case "land_wreck_c130j_cargo":        // Aircraft cargo wreck.
case "land_wreck_caravan_mgreen":     // Caravan/trailer wreck.
case "land_wreck_caravan_mrust":      // Caravan/trailer wreck.
case "land_wreck_caravan_wbrown":     // Caravan/trailer wreck.
case "land_wreck_caravan_wgreen":     // Caravan/trailer wreck.
case "land_wreck_trailer_closed_de":  // Closed trailer dynamic-event wreck.
```
