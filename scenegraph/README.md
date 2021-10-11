# Project 3 — Intersect

### Introduction to Computer Graphics, Fall 2021

*Due Monday, October 18 at 10:00pm*

**Instructions:** Complete this assignment by yourself without any help from anyone or anything except a current CS 1230 TA, the lecture notes, official textbook, and the professor. Submit the assignment on Gradescope no later than 10:00pm on Monday, October 18. You are allowed to use up to 3 late days on this assignment.

## Introduction

In this assignment and the next you will be implementing a basic raytracer, a rendering algorithm that simulates how light rays bounce around a scene (and lets you make really cool-looking images!)

## Requirements

### The Ray Tracing Pipeline

In lecture you learned the basic steps of the raytracing pipeline's inner loop:

- **Generating rays** (simplest case: for Intersect, just shoot a ray through the center of each pixel)
- **Finding** the closest object along each ray
- **Illuminating** samples; you are only required to support point lights

### Implicit Equations

One of the advantages of ray tracing is that you don’t have to work with approximations to the objects in your scenes. When your objects are defined by an implicit equation, you can render that object directly with a resolution as high as your image allows. You need to be able to render the following objects using their implicit equations: Cube, Cylinder, Cone, and Sphere. Basically this means that you will use math to solve *exactly where* a ray intersects a shape instead of approximating the shape with a lot of triangles and sending it to OpenGL.

### A Simple Illumination Model

You will be using a limited illumination model. We only expect you to handle the ambient and diffuse lighting terms of the simple illumination model (no attenuation or shadows yet). You should, however, leave room in your design for a more complex model of illumination. The next assignment, Ray, will extend what you do in this assignment to handle a recursive illumination model.

The global lighting coefficients can be found in `CS123SceneData.h`. You should pay attention to this struct:

```cpp
// Scene global color coefficients
struct CS123SceneGlobalData {
	float ka; // ambient
	float kd; // diffuse
	float ks; // specular
	float kt; // transparent
};
```

In the lighting equation, `ka` is ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20k_a) and `kd` is ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20k_d). You do not have to worry about `ks` and `kt` for now; these will be used in Ray, the next assignment.

We give out a lot of equations for various kinds of illumination, but here is the one we expect you to use for Intersect. Notice that there are no recursive or specular terms and you are not expected to take light attenuation or shadows into account. **This is slightly different from the equation in class, so please use this one.** The main difference is in how the ambient term is calculated. For simplicity, we just use the object’s intrinsic ambient color and the global coefficient, instead of also counting the intensity of an ambient light.

![](https://latex.codecogs.com/svg.latex?%5Cbg_white%5CLARGE%20%20I_%7B%5Clambda%7D%3Dk_%7Ba%7DO_%7Ba%5Clambda%7D&plus;%5Csum_%7Bm%3D0%7D%5E%7B%5Ctext%7BnumLights%7D-1%7D%5Cleft%5BI_%7Bm%5Clambda%7D%5Ccdot%5Cleft%28k_%7Bd%7DO_%7Bd%5Clambda%7D%5Chat%7Bn%7D%5Ccdot%5Chat%7BL%7D_%7Bm%7D%5Cright%29%5Cright%5D)

Here,

- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20I_%5Clambda) is the final intensity for wavelength ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Clambda), in our case the final R, G, or B value of the pixel we want to color
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20k_a) is the global ambient coefficient; `CS123SceheGlobalData::ka` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20O_%7Ba%5Clambda%7D) is the object's ambient color for wavelength ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Clambda), in our case the object's R, G, or B value for ambient color, `CS123SceneMaterial::cAmbient` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20m) is the current light; to compute the final intensity we must add up contributions from all lights in the scene
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Ctext%7BnumLights%7D) is the number of lights in the scene; `CS123XmlSceneParser::getNumLights()` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20I_%7Bm%5Clambda%7D) is the intensity of light ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20m) for wavelength ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Clambda), in our case the R, G, or B value of the light color for light ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20m); `CS123SceneLightData::color` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20k_d) is the global diffuse coefficient, `CS123SceneGlobalData::kd` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20O_%7Bd%5Clambda%7D) is the object’s diffuse color for wavelength ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Clambda), in our case the object’s R, G, or B value for diffuse color; `CS123SceneMaterial::cDiffuse` in the support code
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Chat%20n) is the object's unit length surface normal vector at the point of intersection; this is something you need to compute
- ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20%5Chat%20L_m) is the unit length incoming light vector from light ![](https://latex.codecogs.com/svg.latex?%5Cinline%20%5Cbg_white%20m); think how this might change depending on whether the light is a point or directional light, also make sure this vector is oriented in the correct direction

Just to make everything absolutely clear, you do NOT need to handle attenuation, directional lights, spot lights, area lights, shadows, texture mapping, specular lighting, reflection, super sampling, or multi-threading in this assignment.

You will want to use this equation to compute the R, G and B values independently *for each image pixel*. Note that you need to figure out which object the current ray intersects with before you can use this illumination equation. Please make sure you understand the concepts in lecture before attempting to code the assignment. This assignment is math heavy (more so than Shapes) and it’s easy to get confused. If you get confused you’ll just end up throwing epsilons (small correction terms) everywhere and that will make things even worse.

### Design

A limited amount of support code is provided for ray tracing. Your final (rasterized) output image will reside on the 2D image canvas, the same one you used for Brush. Code carefully! You’ll (hopefully) be reusing all of the code you write in this assignment for Ray. Most of the design, this time, will be your own.

We provide you with a stencil class, `RayScene`, in `RayScene.cpp/h`. In this project you will be creating a raytracer rendering of whatever scene you currently have loaded (via the File/Open menu option).

You can access scenes to open from https://github.com/cs123tas/data, or /course/cs1230/data/scenes on the department machines.

You should make use of your `Scene` code (i.e. the parsing code you wrote for Lab 3). One option would be to let your `Scene` load the scene first, and then create your `RayScene` based on the contents of your `Scene` at the time the Render button on the Ray dock is clicked. A copy constructor might be very useful for exactly this (copy constructors create an object by initializing it with an object of the same class), though there are other ways to get the necessary contents.

You will also need to figure out how to handle implicit shape intersections. You can create new classes for each implicit shape, or you can extend your existing Shapes classes to handle these intersections. Doing this may require modifications to the `Shape.h` interface. Consider the benefits and drawbacks of implementing your implicit shapes separately vs. alongside your existing shapes code.

### Rendering the Scene

When the Render button on the Ray dock is clicked, the `MainWindow::renderImage` function will be invoked, which will in turn need to invoke the `Canvas2D::renderImage` function (which you are responsible for implementing). The camera data that was loaded by the scene file parser (an instance of the `CS123SceneCameraData` struct) will will be passed in as an argument to this function, which you should take into account in your render. You can get the current raytracing settings from the global settings object, as usual. For now, you can ignore basically all of these settings. Note: You will need to modify `MainWindow::renderImage()` to load your RayScene into the canvas before you can render your scene.

You are *not* required to implement marquee selection for this assignment. When Render is clicked, you should render the entire scene, regardless of the marquee bounds.

## FAQ

1. **My raytracer seems to be running slowly.**

	Speeding up ray tracing is difficult. Usually, it is not enough to optimize inner loops, as there is just too much work that needs to be done for ray creation, intersection testing and illumination. For each ray you shoot through the film plane (i.e. for each pixel in your output image) you must test for intersections for each object in your scene. Thus, as the number of objects in the scene increases, the time it takes to render the scene increases exponentially. Note that the film plane is relative to the camera, it is not a coordinate system, but rather a plane that a vector intersects. Further note that matrix operations (especially matrix inverse) can be quite expensive; try to do these calculations as little as possible.

	For extra credit, you can address this problem by implementing a spatial (bounding volume) acceleration data structure. We recommend starting with a basic octree and if you have time, extending that octree to a kd-tree (much like the one you may have made in cs32). Look up the surface area heuristic online or see the lecture slides on aceleration data structures for more information. Many of the TAs have also implemented different optimizations, so you can ask them at TA hours for advice.
2. **Nothing shows up.**

	Before you come to TA hours for help, please double check your math. Liberal use of `assert` statements will definitely help you find errors in your program. Please remember that the TAs are primarily here to help with conceptual problems, not to debug your code.
3. **How can I design Intersect so that doing Ray is an upgrade instead of a rewrite?**

	When you do reflections in Ray you will not only cast rays out from your eye point but also from reflected surfaces. Try to break up your program into different functions to make this transition easier.
4. **Speckles appearing on surfaces**

	Usually this is caused by self-intersection. If you’re casting a ray off a shape, make sure to move the source slightly away from the shape’s surface (by some epsilon term) so it doesn’t intersect with that shape.

## Extra Credit and Half-Credit

### (Optional) Extra Credit

Remember that half-credit requirements count as extra credit if you are not enrolled in the half-credit course.

Here are some examples of extensions you can do for extra credit. Note that we won’t give out double extra credit between Intersect and Ray. If you do multithreading now, for example, you’ll get extra credit for it on Intersect, but not on Ray. On the other hand, Intersect is worth slightly more than Ray. Therefore, 1 point of extra credit you do now is worth more (in terms of your final grade) than 1 point of extra credit you do later. Additionally, other extra credit options will be offered on Ray (in addition to these), so you can do extra credit both times (which is clearly the best of both worlds!).

- **Effective optimizations.** Think about how to reduce the overall number of intersection tests required for a scene. The biggest speed gain can be found by making a “bucket” for each pixel (or small group of pixels) that stores what objects could possibly lie “underneath.” This involves a precomputation step where object bounding boxes are projected into screen coordinates (think backwards mapping!). You can also put 3D bounding cubes or spheres around master objects (like a chess piece) so that you don’t have to check every sub-object if the ray is nowhere close to the master object. The first method will help a lot in Intersect (where rays don’t bounce around), but not as much in Ray. The second method will help with both Intersect and Ray, but actually makes things a bit slower for small scenes. A slightly more complicated, but better than bounding spheres/cubes, solution is to partition your scene with an octree. Better yet, you can extend your octree to divide at an optimal split position (vs. at the midpoint each split); an octree implemented in this way is known as a kd-tree. Having an octree or kd-tree will really pay off in Ray.

- **Multithreading.** If you make your code multi-threaded you can have multiple threads ray tracing different parts of the image concurrently.

- **Other implicitly-defined shapes.** The torus, for example, is described by a quartic on *x*, *y*, and *z*.

- **Antialiasing.** You might try rendering, edge detecting, and then blurring the edges that were detected. You can also shoot out multiple rays per pixel to get less aliasing (supersampling). Supersampling will produce better results than blurring edges, but it’s much slower. Instead of brute force supersampling, try adaptive supersampling for a speed boost.

- **Intersect polygonal meshes.** Wouldn’t it be nice to see a complicated polygonal object ray traced? These objects are composed of a lot of triangles, so you may want to think about some of the optimizations you can do. There are a couple of famous techniques you can implement.

- **Area lights.** You may notice that there is a material property called `cEmissive`. This property indicates the intensity of light being emitted from the corresponding object. It allows you to design a scene that has area lights, which can result in some really cool effects (like *soft shadows*). If you want to implement this feature, you are going to have to trace multiple rays, one to each sample point on the area light source. One way to do this is based on *radiosity* (which you’ll learn about in lecture soon). Divide the surface of your area light (which will be a sphere or a cube, or a mesh triangle) into “patches.” Divide the `cEmissive` evenly across the patches. This approximates the light passing through the corresponding solid angle. In addition to tracing a ray from the intersection point on an object to each light, also trace a ray from the intersection to each patch on each object with a `cEmissive`. You will also need to check for occlusion for each of these shadow rays, as usual.

### Half-Credit Requirements

Remember that half-credit requirements count as extra credit if you are not enrolled in the half-credit course.

**Important note:** Half-credit requirements for Intersect and Ray will be graded when you hand in Ray. However we **strongly** recommend that you begin work on these requirements with Intersect. Otherwise you will be very unhappy.

1. Make your implementation multithreaded! This will make your life a lot easier since scenes will load much faster. Check out the following link for documentation on how to do this: [http://qt-project.org/doc/qt-4.8/threads.html](http://qt-project.org/doc/qt-4.8/threads.html)
2. Implement an accelerated data structure of ![](https://latex.codecogs.com/svg.latex?%5Cbg_white%20O%28n%5Clog%20n%29) time.
3. Implement adaptive supersampling to antialias your scenes.

## Handing In

To hand in your assignment, upload your repo to Gradescope. Please include a **README_Intersect.txt** with your handin containing basic information about your design decisions and any known bugs or extra credit.

For all assignments in this course, we will test your code on department machines, so we expect it to compile on department machines. If you're developing locally, test your code on a department machine before you hand it in. If your code does not compile, we will ask you to resubmit it and will give you a late penalty!
