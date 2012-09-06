Antonov An-2 v3.0 for X-Plane v9.xx
by Mihaly Alberti (ksgy)

---------------------------------------------------------------------------------------------------

CHANGES in v3.0
- Completly rewritten plugin: CHT and oil temp, new starter, real artificial horizon
- Manipulators
- 3D cockpit light
- Normal maps
- FPS otimizations
- Magnetic compass
- Fully functional ADF and gyro-compass
- iPhone GPS


See operation_manual.txt for operation instructions.

Thanks for testers: CAG, Steve, Kotta, Birinyi Balazs ;)
Especially tanks for kotta for the Mac plugin.

---------------------------------------------------------------------------------------------------

CHANGES:
v2.0 Added external and passanger cabin 3D model, plugin
v2.0.1 Fixed ITT bug, the plane now uses the flat plugin model
v2.0.2 Added Mac plugin
v2.0.3 Updated ACF for v9.31, some fps improvements.
v2.0.4 Updated starter plugin, fixed ITT bug when opening A/C after An-2

---------------------------------------------------------------------------------------------------

Release: Jun, 6. 2009

Added:

(1) External model - Original 3D model provided by X-Air Team
(2) Passanger cabin
(3) Plugin for flywheel starter and improved engine model - thanks for ILya Sizikov for his kind help
(4) Template PSD (Photoshop) file for liveries


 * About the plugin:
Firstly: this is just an improvement for the default x-plane engine model and for the flywheel starter.
You don't have to use if you don't want, but it's recommended. (If the plugin is turned off, the engine CHT gauge isn't working!)

Engine fails when:
   * CHT < 120 and throttle > 40%
   * CHT > 245 for 2 mins
   * CHT > 260
   * CHT > 130 when shutting down the engine
   

 * About the flywheel starter:
The An-2 has a special engine starting. Fistly you spin up a flywheel with an electro-motor, after it reached the max rpm, the flywheel will connected to engine.
There is a switch right to the magnetos which has 3 different states:
   * left: connected to engine
   * middle: off
   * right: spin up

When starting you have to hold the switch in right position. After about 15 sec, set switch to left position, which will spin up the engine and apply the starter automatically.
When the engien is start to spin up, apply a little throttle to help the start. If you're unsure how to start, watch this video: http://www.youtube.com/watch?v=sLNvsgUGjS0 :)
Antonov An-2 v2.0 for X-Plane v9.xx


---------------------------------------------------------------------------------------------------

CHANGES:
v2.0 Added external and passanger cabin 3D model, plugin
v2.0.1 Fixed ITT bug, the plane now uses the flat plugin model
v2.0.2 Added Mac plugin
v2.0.3 Updated ACF for v9.31, some fps improvements.
v2.0.4 Updated starter plugin, fixed ITT bug when opening A/C after An-2

---------------------------------------------------------------------------------------------------

Release: Jun, 6. 2009

Added:

(1) External model - Original 3D model provided by X-Air Team
(2) Passanger cabin
(3) Plugin for flywheel starter and improved engine model - thanks for ILya Sizikov for his kind help
(4) Template PSD (Photoshop) file for liveries


 * About the plugin:
Firstly: this is just an improvement for the default x-plane engine model and for the flywheel starter.
You don't have to use if you don't want, but it's recommended. (If the plugin is turned off, the engine CHT gauge isn't working!)

Engine fails when:
   * CHT < 120 and throttle > 40%
   * CHT > 245 for 2 mins
   * CHT > 260
   * CHT > 130 when shutting down the engine
   

 * About the flywheel starter:
The An-2 has a special engine starting. Fistly you spin up a flywheel with an electro-motor, after it reached the max rpm, the flywheel will connected to engine.
There is a switch right to the magnetos which has 3 different states:
   * left: connected to engine
   * middle: off
   * right: spin up

When starting you have to hold the switch in right position. After about 15 sec, set switch to left position, which will spin up the engine and apply the starter automatically.
When the engien is start to spin up, apply a little throttle to help the start. If you're unsure how to start, watch this video: http://www.youtube.com/watch?v=sLNvsgUGjS0 :)


 * About the PSD templates:
The PSD built for easy livery creation. I hope the layers is enough self-explaining for easy using :)
   * external.psd - The external view of An-2
   * passcabin.psd - Passanger cabin & side door
   * external_window.psd - the windshield frames from external view

Checklist for checklister plugin and in simple txt format are included.
It's recommended to follow that otherwise you cannot start or fail the engine.

(The side door can be opened/closed via canopy open/close command)


---------------------------------------------------------------------------------------------------

CHANGES:
v1.2: Aerodynamics improved.

---------------------------------------------------------------------------------------------------

The plane can be flown with the instructions from original POH. There are some smaller
deviations, though. (See below)

Following changes have been implemented:

(1) Geometry changes at Wings (dihedral, angle of incidence) and horizontal stabilizer
    (size, angle of incidence), control surface ranges (elevator) according to data from [1].
    During the decades of manufacturing of the plane the geometry was changed. Now it has the
    state "after 60th series"  

(2) The wings' airfoil have been replaced by TsAGI R-PS 14%. Since no exact profile data could be
    located the airfoil was reverse engineered from plane polars published in [2]. Lift and drag
    for the flaps were adjusted according to data from the same source. Slats could not be tweaked
    since PlaneMaker does not allow to do so.  

    Now the plane can take off at 30 deg flaps to ensure the require STOL performance.

(3) The outer control surfaces of the upper wing are now flaperons as in the original

(4) The mainfold pressure gauge was adjusted to show mainfold pressure in mm Hg.

Limitations:

- Mainfold pressure and rpm settings from the handbook at intermediate power settings
  (50%-75% rated power) yield 5%-8% less power then specified. This seems to be a
  limitation of XP's engine model. A mainfold pressure 30-40 mm higher then in POH has
  to be used to recover the original power.
  A motor peformance curve for the ASh62-IR engine is published in [3] which could be used
  to refine the engine model.   
   

[1] Rukovodstvo po letnoj ekspluatacii samoleta An-2 [russ.]
    (An-2 POH), Moscow 1984

[2] Rekomendacii po prakticheskoj aerodinamike samoleta An-2 [russ.]
    (Suggestions regarding the practical aerodynamics of the An-2), Moscow 1985

[3] Samolet An-2 (The aircraft An-2) [russ.], Moscow 1969


---------------------------------------------------------------------------------------------------

CHANGES:
v1.1: Changed prop from manual pitch to constant rpm prop. Thanks for Stefan for the info.

---------------------------------------------------------------------------------------------------

Release: Jan, 13. 2009
Original author: Pedro van Leeuwen
Modified by with permission: Mihaly Alberti
Liveries: Criminy

The cockpit's features

    * Moving yoke, pedals, throttle, prop. pitch, mixure, etc
    * Hide/show yoke clicking area above the artificial horizont
    * Window icing
    * All instruments 3D
    * Night textures
    * All controls can be draggable by bottom of control
    * Moving Wunderbaum air-fresher :)
    * Fine-tuned flight model for v9.xx


For more info about this plane, visit website: http://x-plane.indexf1.hu/an2/
Flight manual: http://www.agplane.nl/manuals/antonovan2/index.html

Hope you enjoy :)


---------------------------------------------------------------------------------------------------
This package is offered as freeware; as stated under part 2.3 of the 'X-Plane general License' (see included document)
The Package and Derivatives may be redistributed for non-commercial purposes only.

Any new files generated from or based on these originals -in whole or in part- will fall under the same 'copyright license' and should remain 'freeware'.

Please, do always include with the package/derivatives the 'X-Plane general License' document and this 'DNA file' (updated with your XP version no. and short description of your work/adjustmets/modifications)
---------------------------------------------------------------------------------------------------


Installation: simply copy An-2 folder to X-Plane's aircraft folder



 * About the PSD templates:
The PSD built for easy livery creation. I hope the layers is enough self-explaining for easy using :)
   * external.psd - The external view of An-2
   * passcabin.psd - Passanger cabin & side door
   * external_window.psd - the windshield frames from external view

Checklist for checklister plugin and in simple txt format are included.
It's recommended to follow that otherwise you cannot start or fail the engine.

(The side door can be opened/closed via canopy open/close command)


---------------------------------------------------------------------------------------------------

CHANGES:
v1.2: Aerodynamics improved.

---------------------------------------------------------------------------------------------------

The plane can be flown with the instructions from original POH. There are some smaller
deviations, though. (See below)

Following changes have been implemented:

(1) Geometry changes at Wings (dihedral, angle of incidence) and horizontal stabilizer
    (size, angle of incidence), control surface ranges (elevator) according to data from [1].
    During the decades of manufacturing of the plane the geometry was changed. Now it has the
    state "after 60th series"  

(2) The wings' airfoil have been replaced by TsAGI R-PS 14%. Since no exact profile data could be
    located the airfoil was reverse engineered from plane polars published in [2]. Lift and drag
    for the flaps were adjusted according to data from the same source. Slats could not be tweaked
    since PlaneMaker does not allow to do so.  

    Now the plane can take off at 30 deg flaps to ensure the require STOL performance.

(3) The outer control surfaces of the upper wing are now flaperons as in the original

(4) The mainfold pressure gauge was adjusted to show mainfold pressure in mm Hg.

Limitations:

- Mainfold pressure and rpm settings from the handbook at intermediate power settings
  (50%-75% rated power) yield 5%-8% less power then specified. This seems to be a
  limitation of XP's engine model. A mainfold pressure 30-40 mm higher then in POH has
  to be used to recover the original power.
  A motor peformance curve for the ASh62-IR engine is published in [3] which could be used
  to refine the engine model.   
   

[1] Rukovodstvo po letnoj ekspluatacii samoleta An-2 [russ.]
    (An-2 POH), Moscow 1984

[2] Rekomendacii po prakticheskoj aerodinamike samoleta An-2 [russ.]
    (Suggestions regarding the practical aerodynamics of the An-2), Moscow 1985

[3] Samolet An-2 (The aircraft An-2) [russ.], Moscow 1969


---------------------------------------------------------------------------------------------------

CHANGES:
v1.1: Changed prop from manual pitch to constant rpm prop. Thanks for Stefan for the info.

---------------------------------------------------------------------------------------------------

Release: Jan, 13. 2009
Original author: Pedro van Leeuwen
Modified by with permission: Mihaly Alberti
Liveries: Criminy

The cockpit's features

    * Moving yoke, pedals, throttle, prop. pitch, mixure, etc
    * Hide/show yoke clicking area above the artificial horizont
    * Window icing
    * All instruments 3D
    * Night textures
    * All controls can be draggable by bottom of control
    * Moving Wunderbaum air-fresher :)
    * Fine-tuned flight model for v9.xx


For more info about this plane, visit website: http://x-plane.indexf1.hu/an2/
Flight manual: http://www.agplane.nl/manuals/antonovan2/index.html

Hope you enjoy :)


---------------------------------------------------------------------------------------------------
This package is offered as freeware; as stated under part 2.3 of the 'X-Plane general License' (see included document)
The Package and Derivatives may be redistributed for non-commercial purposes only.

Any new files generated from or based on these originals -in whole or in part- will fall under the same 'copyright license' and should remain 'freeware'.

Please, do always include with the package/derivatives the 'X-Plane general License' document and this 'DNA file' (updated with your XP version no. and short description of your work/adjustmets/modifications)
---------------------------------------------------------------------------------------------------


Installation: simply copy An-2 folder to X-Plane's aircraft folder


