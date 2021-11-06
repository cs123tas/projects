# Project 5: Sceneview
### Introduction to Computer Graphics, Fall 2021

*Due Date: 11:59 PM EST on November 11th, 2021*

# Stencil changed

**Stencil has changed at 12:30am Nov 6, EST. Please update your stencil code by pulling or editing manually** 

# Instructions

Complete this assignment by yourself with no help from anyone or anything except a current CS123 TA, the lecture notes, official textbook, and the professor. Hand in the assignment using Gradescope. You are allowed to use up to 3 late days on this assignment.

# Introduction

In Intersect and Ray assignments, you've implemented a ray tracer that projects a 3-dimensional scene on a 2-dimensional plane. In this assignment, you will implement a 3-dimensional scene renderer using components from previous assignments including, Shape, Scenegraph lab, and Camtrans lab. Specifically, once you open a scene file, your program will iterate through the objects in that scene file, and render each object to the screen using the OpenGL wrappers in the stencil and render functions of your shape classes.

## Demo

As usual, we have implemented the functionality you are required to implement in this assignment. Your results should be identical to the results in the demo; this includes camera positioning, camera parameterization, aspect ratio, object locations, object colors, light positions, light attenuations, and light colors. Specifically, you should be able to view the same scene as the demo when you open a scene file.

**Note**: Some scenes have primitives that have similar Z-buffer values and this causes an effect called Z-fighting. The effect causes random pixels to be rendered with the color of one primitive or another in a non-deterministic manner. Don't worry if this happens and your pixels don't exactly match the demo. As long as the primitives are in the correct place (within epsilon) then you have done it correctly.

The demo has functionality for rendering wireframes and normals in sceneview scenes.  This functionality is not required of you and will not be considered for extra credit, but it may be useful for debugging. Look at how it is done in ShapesScene if you would like to implement it yourself.

The demo also implements LOD, which is part of the extra credit for this assignment. So the tessalation of the shapes within the demo will not match the sliders exactly. You are not required to update your scene according the the GUI parameters, and if you  do implement LOD it does not need to match the demo exactly.

Lastly, the demo has the feature that after applying camera transformation (using orbit camera or camtrans camera) to a scene and click render on the ray tab, the same camera transformation is applied to the scene rendered by the ray tracer. You may implement this feature for extra credit. (**Hint**: Implement *getCamearData* method that returns a current snapshot of CS123SceneCameraData in CamtransCamera class, and use that function in MainWindow::renderImage(). The stencil has provided function signatures for getCameraData() and implementations for OrbitaCamera::getCameraData() and QueternionCamera::getCameraData().)

As in Intersect and Ray, you can use test files in [data](https://github.com/cs123tas/data) repository to compare your result with the demo.

# Requirements

Since you have already implemented a scene file parser, **you will be mostly modifying your SceneviewScene.cpp/h files** in scenegraph folder using the information you got from the parser. 

## The Scene Classes

SceneviewScene (which you will complete in this assignment) implements an OpenGLScene. It will hold a list of objects that are to be rendered to the screen. In addition, the SceneviewScene will contain the cumulative transformation matrix for each object. In the *setGlobalData* method, the global data will be set up. In the *setLights* method, the lights will be set up. Then, in the *renderGeometry* method, each object will be rendered (you'll want to call upon your Shapes code for this).

Recall from class that a scene graph's purpose is to deal with hierarchical transformations. Therefore, we have made a distinction in this assignment: objects and lights are part of the scene graph, and the camera is not. The camera is part of the canvas. You will find this distinction to be handy when it comes time to implement additional rendering interfaces. 

In this assignment, you are only responsible for setting up the global data, the objects, and the lights. We take care of setting up the camera for you; your implementation in CamtransCamera will be used automatically by the support code.

**Hint**: You should use *setLight* and *applyMaterial* method of m_phongShader, which take care of a lot of tricky OpenGL stuff for you.

## Rendering the Scene

The rendering of your scene starts in the *paintGL* method found in SupportCanvas3D. This method will invoke the render method in your SceneviewScene. Your SceneviewScene will call *context->getCamera()* to get the current camera from the canvas, load the appropriate matrices into the shader, and then call *renderGeometry*. This is all done for you.

Your job is to fill in the *renderGeometry* method to render the geometry of your scene using OpenGL. You will have to traverse the data structure in your SceneviewScene and render all the shapes by invoking your Shapes code.**You only need to tessellate your shapes once when you load a new scene - be careful not to retessellate your shapes every frame, or else your project might slow down significantly.** You can use m_phongShader to pass the corresponding transformation matrices from your scene graph before rendering the geometry. (Remember OpenGL labs?)

You are not required to use any of the material properties of scene objects except the "diffuse" and "ambient" color properties. These are the only properties that determines the color of an object in Sceneview. You should make use of the CS123SceneMaterial struct and use the *applyMaterial* function in the support code, which wraps a few OpenGL calls for your convenience. This will handle using the material color properties for you. Lastly, remember to implement setGlobalData() to set coefficient values in the shader.

# Grading

Be sure to test your program on as many scenes as possible! Also, this is the time to fix buggy Shapes and Camtrans code. You'll lose points again on Sceneview if your Shapes and/or Camtrans code doesn't work. Also, be sure to pay particular attention to the following areas of your implementation (although this is a non-exhaustive list): 
- Does your program leak memory? 
- Is your implementation efficient? 
- Do all the scenes load correctly?
- Is the lighting correct? 
- Is the camera correct? 

# Extra Credit and Half-Credit

# \[Optional\] Extra Credit

Remember that half-credit requirements count as extra credit if you are not enrolled in the half-credit course.

Texture mapping and other more advanced effects are not part of the basic requirements for this assignment. You may implement them for extra credit. You can also create a particularly interesting scene to get an extra credit.

## Half-Credit Requirements

Remember that half-credit requirements count as extra credit if you are not enrolled in the half-credit course.
1. You must implement OpenGL texture mapping in your scenes. Your implementation must produce scenes that match the demo. Scenes in the /course/cs1230/data/scenes/ray directory have textures.
2. You must also implement adaptive level of detail based on the complexity of the scene. This means that for scenes with many objects in them,
each object should be rendered with fewer triangles than if the scene contained a small number of objects. Look up [level of detail](http://en.wikipedia.org/wiki/Level_of_detail) for more information. Note: many of the examples you will find discuss distance-based or view-dependent level of detail, which you are not required to do!

# Troubleshooting/FAQ

Please check these FAQ entries before coming to TA hours. You should be able to answer any of the questions in the appropriate section before a TA will help you. If you come to hours unprepared, you may be asked to come back the next day, after you have prepared sufficiently.

## Scene too bright

Did you remember to implement setGlobalData function to pass the global data to the shaders? Are your normals correct? Are they normalized? Is the homogeneous coordinate correct? A fault in any one of these can cause the problem.

Your Camtrans may also be buggy. Look back at Camtrans and make sure your shapes all look correct, including the normals. 

Finally, your lighting may be incorrect. Make sure the lights are in the correct place and all required attributes have been set. Look around the support code we have given you and try to find some useful examples for how to do lighting in OpenGL (there definitely are some in there!). 

## Objects incorrectly positioned

Make sure the homogeneous coordinates of all your vectors and points are correct (particularly those loaded from the CS123SceneParser). Generous use of assert statements will help isolate these problems. 

Are you multiplying your matrices in the correct order? Are your transformation matrices correct? Is your camera in the right place? Start out by loading simpler scene files, such as ball.xml (which contains a single blue ball at the origin). Create other simple test scene files, and go from there. 

Note: While OpenGl expects matrices in column-major format and the scene files store matrices in row-major format, the parser will take care of the conversion automatically - you should not have to worry about transposing them.

## Why is the background gray?

The background is gray if you have "draw wireframe" turned on, because if it was black you might not be able to see the black wires against the black background. If you turn off "draw wireframe" the background will change to black.



