## Goal

- Visualization of star system.
- Take photo or record video.
- Customize stars.
- Customize camera behavior.

## Components

- Object:
    - Position: x, y, z, $\theta$, $\phi$, $\psi$
    - Move

- Camera: Object:
    - Field of View: horizontal, vertical
    - Resolution: width, height
    - FPS: 0 for photo
    - Motion: (optional)

- Star: Object:
    - Mass
    - Temperature
    - Fluctuation
    - Intensity
    - Rotation

- Planet: Object (optional):
    - Mass
    - Reflection

- Ray: Object:
    - Intensity
    - Doplher effect: (optional)

## Algorithm

rk45: Solve motion equation

dpdt: Equation of motion

collision: Check collistion between ray and object