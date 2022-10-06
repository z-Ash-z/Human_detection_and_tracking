# Human detection and tracking

A C++ project that detects and tracks humans and returns their position in the robot's frame of reference.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
---

### Authors:

- Aneesh Chodisetty
- Bhargav Kumar Soothram
- Joseph Katakam

## Introduction

  Object detection and tracking is a computer vision task that has become essential for many robot applications. The object detection and tracking is the base for autonomous robots in specific. Suppose there is a autonomous delivery robot that is on a mission, it has to identify objects, track them, convert their coordinates to the robot's frame of reference and then try to avoid it. This project is foucussed on solving this problem using existing state-of-art object detection algorithms.  

As per Acme Robotic's requirement, we will use the input from a monocular camera to detect and track an object. This object is then converted to the robot's frame of reference. This package is then used by Acme in their robotics-based product that will be lauched next year.  

Our system uses YOLOv5 model that is trained using [COCO dataset](https://cocodataset.org/#home) and is built using C++. COCO dataset is a large-scale object detection, segmentation, and captioning dataset. Our system takes an image from a monocular camera, pre-processes the image, passes this image to the trained model, filters out the human object with the highest confidence and then outputs the location of the object in the robot's frame of reference.
  
## Deliverables

The [repo](https://github.com/z-Ash-z/Human_detection_and_tracking.git) containing:
- The project package.
- Proposed work.
- UML diagrams
- CI tests using Travis
- Code coverage using Coveralls
- Proposed design

## System Design

### Development methodology

Agile software development model will be used for the development process.  

### System architecture

The flow of our system is as follows:
![Activity Diagram]()  
The class diagram for the same can be found [here]().

### Project proposal

- The proposal document can be found [here]().  
- The proposal video can be found [here]().  
- The quadchart can be found [here]().  

### Dependencies  

| Name | Version | license |
| :--- | :--- | :--- |
| Ubuntu | 20.04(LTS) | FSF Licenses |
| C++ | 14 | Creative Commons Attribution-ShareAlike 3.0 Unported License |
| OpenCV | 4.6.0 | Apache License 2.0 |
| Cmake | 3.16.3 | BSD 3-clause License |

### Tools used  

| Usage/Type | Tool name | License |
| :--- | :--- | :--- |
| IDE | Visual Studio Code | MIT License |
| CI pipeline | Travis CI | enterprise.travis- ci.com |
| Code coverage | Coveralls | Coveralls, LLC |
| Running tests | Gtests | BSD 3-Clause "New" or "Revised" License |
