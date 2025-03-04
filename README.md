# AJ Control Software

# File structure
```bash
AJ-Drone/
│
├── code/
│   ├── firmware/                     # Drone firmware
│   ├── software_interface/           # Interface logic between drone and software
│
├── docs/
│   ├── overview.md
│   ├── modules/                      # Documentation on individual modules
│
├── include/
│   ├── flightControl.h
│   ├── communication.h
│
├── src/
│   ├── modules/
│   │   ├── flightControl/
│   │   │   ├── flightControl.cpp
│   │   │   ├── flightControl.h
│   │   ├── communication/
│   │   │   ├── communicationHandler.cpp
│   │   │   ├── communicationHandler.h
│   │   ├── sensors/
│   │   │   ├── sensorManager.cpp
│   │   │   ├── sensorManager.h
│   ├── networking/
│   │   ├── networkCommunication.cpp
│   │   ├── networkCommunication.h
│   ├── scripts/
│   ├── tests/
│   │   ├── modules/
│   │   │   ├── flightControl_tests.cpp
│   │   │   ├── communication_tests.cpp
│   ├── config/
│   │   ├── flight_params.yaml
│   │   ├── network_settings.json
│
├── schematics/
│   ├── designs/
│   ├── circuits/
```
