# CORE Code Repository

Welcome to the CORE Code Repository, the Comprehensive Open Roleplay Engine (CORE) development hub. CORE is a modular, skill-based tabletop RPG system designed to provide flexibility, depth, and customization for players and game masters alike. This repository is the foundation for implementing, testing, and expanding CORE mechanics in a digital environment.

---

## Overview

The CORE RPG system uses a simple yet versatile 3d6 roll mechanic, with additional features like boons, banes, and skill modifiers. This repository is structured to facilitate the development of CORE’s mechanics and utilities, separating reusable logic from application-specific implementations.

---

## Project Structure

- **Core**:
  - A static library containing the core mechanics of the RPG system.
  - Includes features like:
    - Dice-rolling logic (e.g., boons and banes).
    - Configurable mechanics for skills and abilities.
    - Utilities for randomization and probability calculations.

- **App**:
  - An executable project that links against the Core static library.
  - Provides tools for testing mechanics, simulating scenarios, or prototyping new features.

- **Vendor**:
  - Third-party dependencies, including Premake binaries for build generation.

- **Scripts**:
  - Build setup scripts for Windows and Linux platforms.

---

## Getting Started

### Cloning the Repository

Clone this repository to your local machine:
```bash
git clone https://github.com/WayneBuschmeyer/CoreCode.git
cd CoreCode
```

### Generating Project Files

Navigate to the `Scripts` directory and run the appropriate setup script:

- **Windows**:
  ```cmd
  Setup-Windows.bat
  ```
- **Linux**:
  ```bash
  ./Setup-Linux.sh
  ```

This will generate Visual Studio (Windows) or Makefiles (Linux) project files. For macOS, duplicate and modify the Linux script as needed.

### Building the Project

1. Open the generated project/solution in your IDE or build system.
2. Build the `Core` static library.
3. Build and run the `App` executable.

---

## Features

### CORE Mechanics

- **3d6 Roll Mechanic**:
  - The foundation of CORE features skill modifiers, boons, and banes.
  - Additional dice rolls can adjust outcomes dynamically, enhancing gameplay.

- **Boons and Banes**:
  - Boons add extra rolls, selecting the best results.
  - Banes add extra rolls, selecting the worst results.

- **Skill Modifiers**:
  - Configurable modifiers for skills and abilities are fully integrated with the roll mechanic.

- **Flexibility**:
  - Mechanics are designed to be modular and adaptable, making it easy to extend or customize rules.

### Modular Design

The Core/App architecture separates reusable mechanics from application-specific logic, allowing:
- Easy reuse of mechanics across multiple tools or applications.
- Clear separation of concerns for better maintainability.

---

## Customization

- **Core Module**:
  - Add or modify mechanics in the Core library to implement your own rules or features.
  - Extend dice-rolling functions, skills, or abilities as needed.

- **App Module**:
  - Use the App project to test game scenarios, prototype new mechanics, or create interactive tools for CORE RPG.

- **Build Scripts**:
  - Customize the build scripts in `Build.lua`, `Core/Build-Core.lua`, and `App/Build-App.lua` to suit your needs.

---

## Roadmap

- **Automated Testing**:
  - Add comprehensive unit tests for all mechanics in the Core module.
  - Validate boons, banes, and custom mechanics under various conditions.

- **Scenario Simulators**:
  - Develop tools for simulating in-game scenarios to aid in balancing and playtesting.

- **Digital Prototypes**:
  - Create interactive tools to assist players and game masters during gameplay.

- **Cross-Platform Support**:
  - Expand support for macOS and other build systems.

---

## Licensing

This project is licensed under the **GNU General Public License v3.0**. See the `LICENSE` file for details.

### Key Points:
- You may copy, distribute, and modify this project as long as you track changes/dates in source files.
- Any modifications to this project must also be open-sourced under GPLv3.
- You must include a copy of the GPLv3 license in any distribution.

---

## Contributing

Contributions are welcome! To contribute:
1. Fork the repository.
2. Create a feature branch.
3. Submit a pull request with a clear description of your changes.

---

## Contact

For questions, suggestions, or feedback:
- **GitHub**: [WayneBuschmeyer](https://github.com/WayneBuschmeyer)
- **Email**: ws.Buschmeyer@gmail.com

---

This repository is designed to support the development and evolution of CORE RPG. Feel free to explore, experiment, and expand on the system to create unique and engaging roleplay experiences!
