mkdir glm\glm
cd glm\glm
svn export --force https://github.com/g-truc/glm.git/trunk/glm .

cd ..\..

mkdir GLFW
cd GLFW
svn export --force https://github.com/glfw/glfw.git/trunk .

cmake .

Pause