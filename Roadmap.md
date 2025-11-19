# VersaMachina Roadmap

(Subject to change without notice, whenever I feel like it)

## **0. Core Foundations (In Progress)**

- [x] ECS foundation using EnTT
- [x] Entity parenting + hierarchy panel
- [x] Inspector with component add/remove/edit
- [x] Project save/load via YAML
- [x] Basic UI layout (dockspace, panels, editor windows)
- [ ] Dirty-flag + autosave system

------

## **1. BlockSpec System**

**Goal:** Define modules (BCMs, lights, relays, sensors, PDMs, BMS, etc.) with metadata, ports, tags, schematic info.

- [ ] BlockSpec schema (YAML)
- [ ] BlockSpec loader
- [ ] Component <-> BlockSpec binding
- [ ] UI for browsing BlockSpecs
- [ ] Built-in library:
  - [ ] Generic connectors
  - [ ] BCM template
  - [ ] Relay module
  - [ ] Light cluster module
  - [ ] Sensor module
  - [ ]  Power distro module

------

## **2. Graph Editor**

**Goal:** Node-based wiring interface tied to BlockSpecs.

- [x] Editor canvas + panning/zoom
- [ ] Node templates generated from BlockSpec
- [ ] Input/output slot definition system
- [ ] Wire creation & deletion
- [ ] Reconnecting wires dynamically
- [x] Node dragging + auto-update of lines
- [ ] Visual crossing/jump arcs
- [ ] Port validation (type, voltage, direction)
- [x] Graph to ECS sync
- [x] ECS to Graph rebuild on load

------

## **3. Harness Modeling**

**Goal:** Represent real physical harness sections.

- [ ] Harness component & UI
- [ ] Drag entities into sections
- [ ] Color-coded harness grouping
- [ ] Physical length tracking
- [ ] Bend/branch metadata
- [ ] Auto-naming & path inference

------

## **4. Export Pipeline**

**Goal:** Generate diagrams and implementation files.

- [ ] SVG wiring diagram exporter
- [ ] PDF export (layout engine)
- [ ] CSV/JSON pin-map export
- [ ] CAN/LIN config export
- [ ] BOM generation (connectors, pins, etc.)

------

## **5. Editor UX / Productivity**

- [x] Undo/redo command stack
- [ ] Search palette (Ctrl+P style)
- [ ] Replace Proggy font with professional UI font
- [x] Theme presets (dark, light)
- [x] Resizable panels with saved layout
- [ ] Context menus everywhere they make sense

------

## **6. Plugin System**

- [ ] Plugin loader (shared libraries)
- [ ] Plugin-defined components
- [ ] Plugin-defined exporters
- [ ] Plugin-defined nodes/BlockSpecs

------

## **7. Vehicles & Subsystems (Examples Library)**

- [ ] EV Controls T2C: full BlockSpec + harness template
- [ ] Vero BMS V2: BlockSpec + wiring example
- [ ] Generic 12V automotive harness template
- [ ] CAN-centric harness template
- [ ] Basic ICE vehicle example

------

## **8. Release & Distribution**

- [ ] Cross-platform packaging (Linux/Windows)
- [ ] Template projects
- [ ] Auto-updater

------

## **9. Future / Stretch Goals**

- [ ] 3D harness viewer (DilligentFx)
- [ ] Auto-routing assistant
- [ ] Fault simulation (shorts, opens, overcurrent)
- [ ] Car-level module library (OEM compatibility packs)
- [ ] Collaborative editing (local multiplayer)