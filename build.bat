@echo off

if not exist Build ( mkdir Build )
if not exist Build\Debug ( mkdir Build\Debug )
if not exist Build\Release ( mkdir Build\Release )

set "ElementBufferClass=Source\Buffer\ElementBuffer.cpp"
set "VertexBufferClass=Source\Buffer\VertexBuffer.cpp"
set "VertexArrayClass=Source\Buffer\VertexArray.cpp"
set "BufferID=-ISource\Buffer"

set "StaticMeshClass=Source\Model\StaticMesh.cpp"
set "MaterialClass=Source\Model\Material.cpp"
set "TextureClass=Source\Model\Texture.cpp"
set "ModelClass=Source\Model\Model.cpp"
set "ModelID=-ISource\Model"

set "CameraClass=Source\Camera\Camera.cpp"
set "CameraID=-ISource\Camera"

set "ShaderClass=Source\Shader\Shader.cpp"
set "ShaderID=-ISource\Shader"

set "STBClass=Source\Lib\stb_image.cpp"

set "AllClasses=%STBClass% %ShaderClass% %CameraClass% %ElementBufferClass% %VertexBufferClass% %VertexArrayClass% %StaticMeshClass% %MaterialClass% %TextureClass% %ModelClass%"

set "IncludeDirectories=-ISource\Lib %ShaderID% %CameraID% %BufferID% %ModelID%"
set "MainFileDirectory=Source\Main.cpp"

set "BuildType=Debug"

set "OutputDirectory=Build\%BuildType%"

set "OutputName=Crafdead"

g++ -o %OutputDirectory%/%OutputName% %MainFileDirectory% %AllClasses% -lglfw3 -lglew32 -lopengl32 %IncludeDirectories%

"%OutputDirectory%\%OutputName%.exe"