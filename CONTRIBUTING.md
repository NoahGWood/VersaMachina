# Contributing to VersaMachina

Thanks for your interest in contributing!  
VM aims to become a modern, open ecosystem for designing automotive electrical systems.  
We welcome contributions of all types: code, documentation, block libraries, hardware, and ideas.

---

# How to Contribute

## 1. Reporting Issues
Please include:
- clear description of the bug or feature  
- steps to reproduce (if applicable)  
- logs or screenshots  
- expected behavior vs actual behavior  

Use labels if possible.

---

## 2. Submitting Pull Requests
PRs should:
- be focused on a single feature or fix  
- include a clear summary of the change  
- reference related issues (e.g., “Fixes #12”)  
- include tests or example packs where appropriate  

Before submitting:
1. Ensure the code builds on supported platforms.  
2. Run validators on any BlockSpec/Packs added.  
3. Confirm formatting and lint rules (TBD).  

---

## 3. BlockSpec / Pack Contributions
We strongly encourage contributions of:
- ECUs  
- PDMs  
- BCMs  
- sensors  
- switches  
- gateway modules  
- community reverse-engineered components  

Please follow:
- the BlockSpec schema in `docs/specs/BlockSpec.md`  
- the pack manifest format  
- versioning scheme (`vendor:module@major.minor.patch`)  
- clean IDs (e.g. `ford:bcm_2013`, `bosch:abs_unit_gen3`)  

---

## 4. Documentation Contributions
Useful additions include:
- tutorials  
- examples  
- troubleshooting guides  
- schema clarifications  
- sample vehicle builds  

Place docs under `/docs`.

---

# Code Style & Standards
Coming soon (formatting, naming, conventions).  
Until then, keep code clean, documented, and consistent.

---

# Community
Once established, contributors will be invited to join:
- discussions  
- planning  
- roadmap refinement  
- pack registry curation  

We’re building an open ecosystem—your help matters.

---

# License
By contributing, you agree that your contributions may be distributed under the project’s license (to be finalized).

Thanks for helping build VersaMachina!