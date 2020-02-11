import os

GemeratedProjectFilePath = os.getcwd() + "\\..\\Engine.vcxproj"
ManualyCreatedProjectFilePath = os.getcwd()+ "\\ProjectContent.txt"

generatedProjectFile = open(GemeratedProjectFilePath,"r")
manualyCreatedProjectFile = open(ManualyCreatedProjectFilePath,"r")

manualyCreatedProjectData = manualyCreatedProjectFile.read()
generatedProjectData = generatedProjectFile.read()

indexOfItemGroups = generatedProjectData.find("<ItemGroup>")
itemGroups = generatedProjectData[indexOfItemGroups:len(generatedProjectData)]

manualyCreatedProjectFile.close()
generatedProjectFile.close()

generatedProjectFile = open(GemeratedProjectFilePath,"w")
generatedProjectFile.write(manualyCreatedProjectData+itemGroups)
generatedProjectFile.close()
