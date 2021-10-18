# Project 6: Ray
### Introduction to Computer Graphics, Fall 2021

*Due Date: 10:00 PM EST on November 1st, 2021*

# Instructions

Complete this assignment by yourself with no help from anyone or
anything except a current CS123 TA, the lecture notes, official
textbook, and the professor. Hand in the assignment using Gradescope
(which you'll learn about through other handins) no later than 10:00 PM
on November 1st You are allowed to use up to 3 late days on this assignment.

# Introduction

With Intersect, you saw a glimpse of what you could do with a rendering
algorithm that stressed quality over speed. Truly curved surfaces are
possible, and everything has a sort of "perfect" feel to it. As you may
have noticed, there are a few things that our renderer does not yet
handle. For example, what happens if you have a shiny surface? What
about texture mapping? These issues and more are addressed in this
assignment. In Ray, you will be filling out the renderer you wrote for
Intersect to support reflections, texture mapping, shadows, more
advanced lighting, and perhaps even transparency, motion blur, spacial
subdivision, or bump mapping.

The demo for this project is the same as Intersect. Run cs1230_demo at a
shell prompt, and load a scene file using the menu. This time, try some
of the files in the "ray" scene folder, and be sure to enable the more
advanced options in the ray tracing toolbox.

There is no additional support code for Ray; in this assignment, you are
building entirely on your Intersect code.

# Requirements

For this project you are required to extend your Intersect code to
implement additional features in your ray tracer. Your ray tracer must
be able to handle:

-   Reflection

-   Texture mapping for, at least, the cube, cylinder, cone, and sphere

-   Specular highlights

-   Shadows

-   Directional lighting

-   Light fall-off (attenuation)

To calculate the intensity of the reflection value, you need to
determine the reflection vector based on an object's normal and the look
vector. You then need to recursively calculate the intensity at the
intersection point where the reflection vector hits. With each
successive recursive iteration, the contribution of the reflection to
the overall intensity drops off. For this reason, you need to set a
limit for the amount of recursion with which you calculate your
reflection. You must make it possible to change the recursion limit
easily[^1] because the TA may want to change it during grading. Also,
you will want to terminate the recursion when the intensity of the
contributed color drops below a reasonable threshold.

Just to review, the lighting model you will be implementing is:

<a href="https://www.codecogs.com/eqnedit.php?latex=I_{\lambda}=k_{a}O_{a\lambda}&plus;\sum_{i=1}^{m}f_{att\,i}I_{\lambda\,i}\left[k_{d}O_{d\lambda}(\hat{N}\cdot\hat{L}_{i})&plus;k_{s}O_{s\lambda}(\hat{R}_{i}\cdot\hat{V})^{n}\right]&plus;k_{s}O_{r\lambda}I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{\lambda}=k_{a}O_{a\lambda}&plus;\sum_{i=1}^{m}f_{att\,i}I_{\lambda\,i}\left[k_{d}O_{d\lambda}(\hat{N}\cdot\hat{L}_{i})&plus;k_{s}O_{s\lambda}(\hat{R}_{i}\cdot\hat{V})^{n}\right]&plus;k_{s}O_{r\lambda}I_{r\lambda}" title="I_{\lambda}=k_{a}O_{a\lambda}+\sum_{i=1}^{m}f_{att\,i}I_{\lambda\,i}\left[k_{d}O_{d\lambda}(\hat{N}\cdot\hat{L}_{i})+k_{s}O_{s\lambda}(\hat{R}_{i}\cdot\hat{V})^{n}\right]+k_{s}O_{r\lambda}I_{r\lambda}" /></a>

Here, the subscripts <a href="https://www.codecogs.com/eqnedit.php?latex=a" target="_blank"><img src="https://latex.codecogs.com/gif.latex?a" title="a" /></a>, <a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a>, <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a>, and <a href="https://www.codecogs.com/eqnedit.php?latex=r" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r" title="r" /></a> stand for ambient, diffuse,
specular, and reflected, respectively.

- <a href="https://www.codecogs.com/eqnedit.php?latex=I_{\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{\lambda}" title="I_{\lambda}" /></a>: is the intensity of the light (or for our purposes, you can just
    think of it as the color) and the <a href="https://www.codecogs.com/eqnedit.php?latex=\lambda" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\lambda" title="\lambda" /></a> subscript is for each
    wavelength (red, green, and blue).

- <a href="https://www.codecogs.com/eqnedit.php?latex=k" target="_blank"><img src="https://latex.codecogs.com/gif.latex?k" title="k" /></a>: is a constant coefficient. For example, <a href="https://www.codecogs.com/eqnedit.php?latex=k_{a}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?k_{a}" title="k_{a}" /></a> is the ambient coeff.

- <a href="https://www.codecogs.com/eqnedit.php?latex=O" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O" title="O" /></a>: is the color of the object being hit by the ray. For example,
    <a href="https://www.codecogs.com/eqnedit.php?latex=O_{d\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O_{d\lambda}" title="O_{d\lambda}" /></a> is the diffuse color at the point of ray intersection
    on the object.
- <a href="https://www.codecogs.com/eqnedit.php?latex=m" target="_blank"><img src="https://latex.codecogs.com/gif.latex?m" title="m" /></a>: is the number of lights.

- <a href="https://www.codecogs.com/eqnedit.php?latex=f_{att\,i}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?f_{att\,i}" title="f_{att\,i}" /></a>: is the attenuation for light <a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>.

- <a href="https://www.codecogs.com/eqnedit.php?latex=I_{\lambda\,i}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{\lambda\,i}" title="I_{\lambda\,i}" /></a>: is the intensity of light <a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>.

- <a href="https://www.codecogs.com/eqnedit.php?latex=\hat{N}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\hat{N}" title="\hat{N}" /></a>: is the normalized normal to <a href="https://www.codecogs.com/eqnedit.php?latex=O" target="_blank"><img src="https://latex.codecogs.com/gif.latex?O" title="O" /></a> at the point of intersection.

- <a href="https://www.codecogs.com/eqnedit.php?latex=\hat{L}_{i}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\hat{L}_{i}" title="\hat{L}_{i}" /></a>: is the normalized vector from the intersection to light <a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>.

- <a href="https://www.codecogs.com/eqnedit.php?latex=\hat{R}_{i}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\hat{R}_{i}" title="\hat{R}_{i}" /></a>:   is the normalized, reflected light from light <a href="https://www.codecogs.com/eqnedit.php?latex=i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?i" title="i" /></a>

- <a href="https://www.codecogs.com/eqnedit.php?latex=\hat{V}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\hat{V}" title="\hat{V}" /></a>: is the normalized line of sight

- <a href="https://www.codecogs.com/eqnedit.php?latex=n" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n" title="n" /></a>:   is the specular exponent

- <a href="https://www.codecogs.com/eqnedit.php?latex=I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{r\lambda}" title="I_{r\lambda}" /></a>:   is the intensity of the reflected light

Please note that this equation is slightly different that from the
slides. **You are expected to implement** ***this*** **equation.** The
main difference is in how the ambient color is calculated. We just use
the color of the object instead of also counting the intensity of an
ambient light.

## Reflection

The most exciting part of this assignment is implementing specular
inter-object reflection! Suppose you are calculating the color of a
pixel <a href="https://www.codecogs.com/eqnedit.php?latex=p" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p" title="p" /></a>. The ray <a href="https://www.codecogs.com/eqnedit.php?latex=r_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_0" title="r_0" /></a> you shot through pixel <a href="https://www.codecogs.com/eqnedit.php?latex=p" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p" title="p" /></a> intersects surface
<a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>. Evaluate the lighting model above at the surface <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>. At this
point, we know all of the terms in the equation *except for*
<a href="https://www.codecogs.com/eqnedit.php?latex=I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{r\lambda}" title="I_{r\lambda}" /></a>, the light reflected onto <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a> by other objects. To
calculate <a href="https://www.codecogs.com/eqnedit.php?latex=I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{r\lambda}" title="I_{r\lambda}" /></a>, we will shoot another ray, starting from
<a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>. This ray, <a href="https://www.codecogs.com/eqnedit.php?latex=r_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_1" title="r_1" /></a>, will be the reflection of <a href="https://www.codecogs.com/eqnedit.php?latex=r_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_0" title="r_0" /></a> about the
surface normal at <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>.

Then, we do the same thing all over again! If <a href="https://www.codecogs.com/eqnedit.php?latex=r_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_1" title="r_1" /></a> intersects an object
at surface point <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>, then we calculate the lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>.
If our maximum recursion depth were 1, then we would know that the color
we calculated from the lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a> would equal the reflected
light we need to take into account at <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>. In other words, the color
calculated at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a> (without adding the contribution of reflected light
on <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>) would equal <a href="https://www.codecogs.com/eqnedit.php?latex=I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{r\lambda}" title="I_{r\lambda}" /></a> at <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a>.

Suppose our maximum recursion depth were 2. Then, we would shoot another
ray <a href="https://www.codecogs.com/eqnedit.php?latex=r_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_2" title="r_2" /></a> out from <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>. The ray <a href="https://www.codecogs.com/eqnedit.php?latex=r_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_2" title="r_2" /></a> is the reflection of <a href="https://www.codecogs.com/eqnedit.php?latex=r_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_1" title="r_1" /></a>  about
the surface normal at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>. If <a href="https://www.codecogs.com/eqnedit.php?latex=r_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_2" title="r_2" /></a> does not intersect any objects,
then the intensity of the reflected light on <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a> would be the
evaluation of the lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>. If <a href="https://www.codecogs.com/eqnedit.php?latex=r_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r_2" title="r_2" /></a> intersects another
object, then the intensity of the reflected light on <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a> (i.e.
<a href="https://www.codecogs.com/eqnedit.php?latex=I_{r\lambda}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?I_{r\lambda}" title="I_{r\lambda}" /></a>) will be the evaluation of the lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_2" title="s_2" /></a>
(without adding the contribution of reflected light on <a href="https://www.codecogs.com/eqnedit.php?latex=s_2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_2" title="s_2" /></a>). The
intensity of reflected light on <a href="https://www.codecogs.com/eqnedit.php?latex=s_0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_0" title="s_0" /></a> would be the evaluation of the
lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a> (adding the contribution of reflected light on
<a href="https://www.codecogs.com/eqnedit.php?latex=s_1" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_1" title="s_1" /></a>).

For a maximum recursion depth of <a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a>, we will recur until we get to
surface point <a href="https://www.codecogs.com/eqnedit.php?latex=s_d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_d" title="s_d" /></a>, or until we shoot out a ray that does not intersect
anything. Remember that when we get to surface point <a href="https://www.codecogs.com/eqnedit.php?latex=s_d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_d" title="s_d" /></a>, we do not
want to recur any more. Therefore, we do not take into account reflected
light when evaluating the lighting model at <a href="https://www.codecogs.com/eqnedit.php?latex=s_d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s_d" title="s_d" /></a>.

## Texture Mapping

A "blend" value may be supplied as a material property for objects that
are texture mapped. If the blend value is 1, then the texture entirely
replaces the diffuse color of the object. If the blend value is 0, then
the texture will be invisible. If the blend value is between 0 and 1,
then you should perform linear interpolation in the same fashion as the
flow rate in Brush.

**The texture images in the scenefiles are specified by absolute paths
on the department file system. If you are working on the project
locally, then you must change the texture paths in the scenefiles so
that they are absolute paths to the textures on your local file system.
All of the scenefiles and textures are in the** `data` **repo**.

## Shadows

Suppose you are calculating the color of a surface point <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a>. For each
point light <a href="https://www.codecogs.com/eqnedit.php?latex=\ell" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\ell" title="\ell" /></a> in the scene, send a ray <a href="https://www.codecogs.com/eqnedit.php?latex=r" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r" title="r" /></a> (a "shadow ray\") from
<a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a> to <a href="https://www.codecogs.com/eqnedit.php?latex=\ell" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\ell" title="\ell" /></a>. If <a href="https://www.codecogs.com/eqnedit.php?latex=r" target="_blank"><img src="https://latex.codecogs.com/gif.latex?r" title="r" /></a> intersects any objects on the way from <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a> to
<a href="https://www.codecogs.com/eqnedit.php?latex=\ell" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\ell" title="\ell" /></a>, then <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a> is occluded and you should not take into account the
contribution of light from <a href="https://www.codecogs.com/eqnedit.php?latex=\ell" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\ell" title="\ell" /></a> to <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a>.

For each directional light <a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a>, you will follow the same process as you
did with point lights. However, as explained below, directional lights
do not have a position. A surface point <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a> will be considered occluded
if the shadow ray starting at <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a> and pointing in the opposite direction
of <a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a> intersects *any* object in the scene. In other words, we are
pretending that the directional light is positioned infinitely far away
from <a href="https://www.codecogs.com/eqnedit.php?latex=s" target="_blank"><img src="https://latex.codecogs.com/gif.latex?s" title="s" /></a>.

## Directional Lighting

A directional light is only specified by a direction. You will use this
direction to calculate the diffuse and specular contribution of a
direcitonal light on a surface. Since a directional light does not have
a position, and therefore there is no concept of "distance away from a
directional light\", **you will not use attenuation with directional
lights**.

## Attenuation

You must implement attenuation for point lights. To do this, you will
multiply the contribution of a point light to a surface by

<a href="https://www.codecogs.com/eqnedit.php?latex=\text{min}\left(\frac{1}{c_{\text{constant}}&space;&plus;&space;d&space;\cdot&space;c_{\text{linear}}&space;&plus;&space;d^2&space;\cdot&space;c_{\text{quadratic}}},&space;\;1\right)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\text{min}\left(\frac{1}{c_{\text{constant}}&space;&plus;&space;d&space;\cdot&space;c_{\text{linear}}&space;&plus;&space;d^2&space;\cdot&space;c_{\text{quadratic}}},&space;\;1\right)" title="\text{min}\left(\frac{1}{c_{\text{constant}} + d \cdot c_{\text{linear}} + d^2 \cdot c_{\text{quadratic}}}, \;1\right)" /></a>

where <a href="https://www.codecogs.com/eqnedit.php?latex=d" target="_blank"><img src="https://latex.codecogs.com/gif.latex?d" title="d" /></a> is the distance from the point light to the surface. This is
exactly how you implemented attenuation in Lab 3. Take a look at the
`CS123SceneLightData` struct in `lib/CS123SceneData.h`. The `function`
field of this struct contains the constants
<a href="https://www.codecogs.com/eqnedit.php?latex=(c_{\text{constant}},&space;c_{\text{linear}},$&space;and&space;$c_{\text{quadratic}})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?(c_{\text{constant}},&space;c_{\text{linear}},$&space;and&space;$c_{\text{quadratic}})" title="(c_{\text{constant}}, c_{\text{linear}},$ and $c_{\text{quadratic}})" /></a>
you will need to compute attenuation. Specifically, `function.x` =
<a href="https://www.codecogs.com/eqnedit.php?latex=c_{\text{constant}}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?c_{\text{constant}}" title="c_{\text{constant}}" /></a>, `function.y` = <a href="https://www.codecogs.com/eqnedit.php?latex=c_{\text{linear}}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?c_{\text{linear}}" title="c_{\text{linear}}" /></a>, and
`function.z` = <a href="https://www.codecogs.com/eqnedit.php?latex=c_{\text{quadratic}}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?c_{\text{quadratic}}" title="c_{\text{quadratic}}" /></a>.

# Testing

Your ray tracer's output should look exactly like the demo (for a given
scene file and render settings). In addition, the directory
`/course/cs1230/data/scene/ray` (i.e. `data/scene/ray` in the `data`
repo) contains scenefiles that specifically test the new features in
Ray. That said, you should not ignore the other scenefiles. Make sure
all of the other files (especially chess) work perfectly as well. Also,
pay particular attention to the orientation of your textures.

If you create your own additional scene files, please put them in
`/course/cs1230/data/scene/shared` so that other students may benefit
from them. We'll also be awarding extra credit for particularly
interesting scenes.

# FAQ

## Texture Mapping SNAFUs

When texture mapping planes you need to be careful. If you're texture
mapping the negative <a href="https://www.codecogs.com/eqnedit.php?latex=z" target="_blank"><img src="https://latex.codecogs.com/gif.latex?z" title="z" /></a> face of the cube, you'll be mapping the
intersection point's <a href="https://www.codecogs.com/eqnedit.php?latex=x" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x" title="x" /></a> position to the <a href="https://www.codecogs.com/eqnedit.php?latex=u" target="_blank"><img src="https://latex.codecogs.com/gif.latex?u" title="u" /></a> in <a href="https://www.codecogs.com/eqnedit.php?latex=(u,v)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?(u,v)" title="(u,v)" /></a> space. The
problem is when you go left-to-right on that face, your <a href="https://www.codecogs.com/eqnedit.php?latex=x" target="_blank"><img src="https://latex.codecogs.com/gif.latex?x" title="x" /></a> values are
actually going from positive to negative. This isn't the only cube face
that something like this will happen on, so use `cube_test.xml` to check
each face.

To texture map the cone, just do it the same way as a cylinder (except
there's only one cap, of course).

## QImage and QString classes

We strongly recommend you look at the documentation for the
[QImage](http://doc.qt.io/qt-4.8/qimage.html) and
[QString](http://doc.qt.io/qt-5/qstring.html) classes. The QImage class
provides an image representation that allows direct access to pixel data
(hint, hint) and this class can require a QString to be passed into it.
You can also search the support code for uses of QImage for reference.

## Speckles appearing on shapes

Usually this is caused by self-intersection. If you're casting a ray off
a shape, make sure to move the source slightly away from the shape's
surface (by some epsilon term) so it doesn't intersect with that shape.

# Extra Credit and Half-Credit

## \[Optional\] Extra Credit

Remember that half-credit requirements count as extra credit if you are
not enrolled in the half-credit course.

Ray is one of the coolest projects you'll ever write at Brown. You, yes,
you, can make it even cooler by doing some sweet extra credit. Here are
some ideas (book sections are included if there's significant discussion
of the topic):

Antialiasing:   Brute force supersampling isn't hard to do and antialiased images
    look really sexy. If you're feeling brave, try your hand at adaptive
    supersampling (15.10.4) or stochastic supersampling (16.12.4)

Transparency:   (16.5.2)

Motion blur 

Depth-of-field

Fewer intersection tests:   (15.10.2) Bounding volumes, hierarchical bounding volumes, octrees,
    and kd-trees are all things to try that will get big speedups on
    complex scenes since most of the clock cycles go to intersection
    tests. Mucho bonus points if you do one of these. Really fast
    intersection tests might get you a few points too, but only if
    they're really good. It is highly *encouraged* that you do some sort
    of spacial subdivision, but certainly not required at all.

Constructive solid geometry:   (a.k.a. CSG, 12.7)

Bump mapping:   Like texture mapping, except each texel contains information about
    the normals instead of color values. It's a great way to "add"
    geometry to an object without having to actually render the
    geometry.

Texture mapping:   and/or intersecting other shapes, like the torus

Spotlights:   Spotlights have position, direction, and an aperture in degrees. If
    a light is a spotlight, `CS123SceneLightData`'s `m_type` will be
    equal to `LIGHT_SPOT` and `m_aperture` will contain the aperture
    size.

Optimizations:   Be careful here. "Premature optimization is the root of all
    evil."[^2] You'll learn that he's right at some point in your
    career, but let's not learn that lesson on Ray. Get the basic
    functionality done then go for the gusto. You may find profiling
    tools like the Valgrind Function Profiler under QtCreator's Analyze
    tab useful. This isn't as important as it once was now that we have
    blazing fast machines, admittedly, but it's still awful fun. CS123
    used to render ray-traced images on Apollo workstations in the Sun
    lab; in some cases, it would take an entire night to generate a
    16x16 pixel image!

Multithreading:   Raytracing is "embarrassingly parallel" because a ray does not
    depend on the outcome of any of the other rays. Each ray cast per
    scanline can be made into its own thread. Feel free to use QThreads
    to help.

Texture filtering:   (bilinear, trilinear, what have you)

Whatever else you can think of!    

Remember to make a few scenefiles to show off the extra credit you did.
If you create your own additional scene files, please put them in
`/course/cs1230/data/scene/shared` so that other students may benefit
from them. We'll also be awarding extra credit for particularly
interesting scenes.

## Half-Credit Requirements

Remember that half-credit requirements count as extra credit if you are
not enrolled in the half-credit course.

**Important Note**: Half-credit requirements for Intersect and Ray will
be graded when you hand in Ray. However we ***strongly*** recommend that
you begin work on these requirements with Intersect. Otherwise you will
be very unhappy.

1.  Make your implementation multithreaded! This will make your life a
    lot easier since scenes will load much faster. Check out the
    following link for documentation on how to do this:
    <http://doc.qt.io/qt-4.8/threads-starting.html>

2.  Implement an accelerated data structure of O(nlogn) time.

3.  Implement adaptive supersampling to antialias your scenes.

# Handing In

To hand in your assignment, upload your repo to Gradescope. Please include a README_Ray.txt with your handin containing basic information about your design decisions and any known bugs or extra credit.

For all assignments in this course, we will test your code on department machines, so we expect it to compile on department machines. If you're developing locally, test your code on a department machine before you hand it in. If your code does not compile, we will ask you to resubmit it and will give you a late penalty!

[^1]: By "easily," we mean that we should only have to change it in
    *one* place. A `const int` in a common header file would be an
    excellent example of a good location to store such a parameter. You
    should document the location of this parameter in your
    README_Ray.txt file.

[^2]: Knuth
