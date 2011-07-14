import re
import os
import sys

#reads name file and returns project dir , insertions and deletions for every project as a tuple
def getProjectsData(name):
    projectsData=[]
    f=open(name,"r")
    lines=f.readlines()
    for index in range(1,len(lines),3):#we dont need first element because it is number of projects
        projectsData.append([lines[index][:-1],lines[index+1][:-1],lines[index+2][:-1]])#make a list of lists ( where each list is a project)

    f.close()
    return projectsData

# I think i can make one regular expression for one commit.
def getDataFromRaw(name):
    list=[]
    f=open("raw","r")
    list.append(f.readline()[:-1])#first line is a project dir
    gitLog=f.read()
    #TODO get the whole name , but not the part before space. I need to get evety thing between author and <email>
    info=re.findall(r"Author: (\S+) <.+\n.+\n\n.+\n\n.+ (\d+) insertions\S+, (\d+) deletions",gitLog)

    f.close()

    #now we will sum all the info if it belongs to "name"
    insertionsSum = 0
    deletionsSum = 0
    for i in range(len(info)):
        if info[i][0]==name:
            insertionsSum+=int(info[i][1])
            deletionsSum+=int(info[i][2])

    list.append(str(insertionsSum))
    list.append(str(deletionsSum))

    return list

def editProjectsData(projectsData,newData):
    inProjects=False #var that shows if newData project is already in projectsData
    for info in projectsData:
        if info[0]==newData[0]:
            inProjects=True
            info[1]=newData[1] #inserions
            info[2]=newData[2] #deletions
    if not inProjects:#if it is a new project
        projectsData.append(newData)

    return projectsData


def saveProjectsData(projectsData,name):
    f=open(name,"w+")
    f.write(str(len(projectsData))+"\n")
    for project in projectsData:
        for info in project:
            f.write(info+"\n")


    f.close()


##MAIN##
#TODO DO not write in a file if there are no instrions and deletions for a "name"
if len(sys.argv)==2:
    name=sys.argv[1]
    
#If file with name "name" exits then we get data from it
#Else we make this file and a empty list
#projectData stores information for one project like that [dirName,insertions,deletions]
    if os.path.exists(name):
        projectsData=getProjectsData(name)
    else:
        os.path.dirname(name)
        projectsData=[]
#Then we get data from "raw" file
    newData=getDataFromRaw(name)
#Change data in projectsData if it is needed
    projectsData=editProjectsData(projectsData,newData)
#Save projectsData to a file
    saveProjectsData(projectsData,name)
else:
    print("Error: no Name. Usage : python parseRaw.py yourGitName")
