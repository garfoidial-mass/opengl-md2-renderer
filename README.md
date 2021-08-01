# opengl-md2-renderer

This is a quake 2 model renderer that I wrote to learn opengl. As it was a learning project, it can probably be improved and optimized a ton, and if you for some reason
end up using this code, I recommend you try.

Dependencies: requires glm, glew and glfw3, along with some header files from the common folder found here: https://github.com/opengl-tutorials/ogl.
It also requires opengl32.lib and glu32.lib to be linked. I compiled this using visual studio 2019.

It's pretty obvious what the .vertexshader and .fragmentshader files are, but I'll give a description anyway. StandardshadingRTT.vertexshader is the vertex shader for
animated models. It handles model interpolation. StandardShadingRTT.fragmentshader is the fragment shader for both static and animated models. passthrough.vertexshader 
and normaltexture.fragmentshader are used for rendering to a texture. Changing around the fragment shader can result in some fun effects, so I've included another shader
that makes the screen wobbly (wavytexture.fragmentshader).

If you want to understand the md2 file format, look here: http://tfc.duke.free.fr/coding/md2-specs-en.html

This is the set of tutorials I followed to start learning opengl (they're really good): http://www.opengl-tutorial.org/

Good luck with whatever you're doing!
