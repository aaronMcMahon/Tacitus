# Tacitus
An application to capture your research experience and share it with another or your future self.

---

##Concepts
Research - to go about seeking

Tacit Knowledge - Knowledge that is difficult to verbalize.  We know more than we can tell.

---

##Statement of Problem

Conducting research is an experience.  This experience costs you time and effort.  Your reward is knowledge.  Recordinging this hard won knowledge costs you time and effort.  Your reward is managed knowledge, which can be shared with a colleauge or yourself.  Unfortunately, we are inefficient in recording knowledge gained from our research experiences due to time and effort constraints.  If we reduce the time and effort required for recording knowledge, we will realize more value from it.    Let's capture the experience of research in a way that allows others to relive that experience .    

---

##Model for capturing information during research

All models are wrong, but some models are useful.  A node link model is useful for expressing the research experience.  Tacitus includes three types of nodes:  

1. Documents - reports, books, websites, tables, drawings, etc.

2. Actions - A small piece of work a researcher undertakes

3. Observations - a concise statment describing a key observation made by a resercher

The relationships between these nodes are expressed as links. Tacitus includes four types of links:

1. Action yields Document - In conducting an Action, the researcher produces a Document (e.g. web search (Action) yields a wikipedia page (Document))

2. Action yields Observation - In conducting an Action, the researcher produces an Observation (e.g. statistical analysis (Action) yields "I think the results are biased" (Observation))

3. Document used by Action - The researcher uses a Document during execution of an Action (e.g. report (Document) was read (Action))  

4. Observation addressed by Action - Action executed in an attempt to follow-up on a previously recorded observation (e.g. "costs seem high" (Observation) assessed with a review of costs (Action))

---

##Application 
Tacitus was written in C++ using Microsoft Visual Studio 2013

##Build Instructions
Using Microsoft Visual Studio 2013
1. Go to File>New>Project
2. In the New Project window under Templates, select Visual C++>CLR
3. In the adjacent field, select CLR Empty Project
4. Name the new project knowledgeForm
5. Press OK
6. Close Visual Studio
7. Copy and paste all files in the Source folder of this repository to your newly created Visual Studio project folder.
	- the directory should be ...\knowledgeForm\knowledgeForm\
	- you will be replacing two existing files (knowledgeForm.vcxproj and knowledgeForm.vcxprj.filters)
8. Restart Visual Studio and open the knowledgeForm project
9. Press Ctrl+Shft+B to build the solution
10. Using Windows Explorer, navigate to the folder that contains the newly created knowledgeForm.exe file created in step 9
11. Copy and paste all files in the Dependencies foler of this repository to the folder opened in step 10
12. Double click knowledgeFrom.exe to run the program




