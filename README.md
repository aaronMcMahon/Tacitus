# Tacitus
Increase your capacity for creative problem solving by unburdening your brain of the effortful and mundane task of record keeping.

Tacitus is a free open-source application that facilitates a unique approach to knowledge management.  It allows you to keep track of:

1. What you did
2. Why you did it
3. What you used 
3. What you produced
4. What you thought
5. How all that relates to what you did next   

![] (GIF.gif)

---

##Statement of Problem

Recording knowledge gained is too hard and too slow.  Using recorded knowledge is too hard and too slow. We need a unique way of thinking about knowledge (a model) and a tool for using that knowledge (an application) that makes things easier and faster. 

---

##The Model

I propose to model the research experience as a system of nodes and links.  This system includes three types of nodes:  

1. Documents - reports, books, websites, tables, drawings, etc.

2. Actions - A small piece of work a researcher undertakes

3. Observations - a concise statement describing a key observation made by a researcher

The relationships between these nodes are expressed as links. There are four types of links:

1. Action yields Document - In conducting an Action, the researcher produces a Document (e.g. web search (Action) yields a Wikipedia page (Document))

2. Action yields Observation - In conducting an Action, the researcher produces an Observation (e.g. statistical analysis (Action) yields "I think the results are biased" (Observation))

3. Document used by Action - The researcher uses a Document during execution of an Action (e.g. report (Document) was read (Action))  

4. Observation addressed by Action - Action executed in an attempt to follow-up on a previously recorded observation (e.g. "costs appear high" (Observation) assessed with a detailed review of costs (Action))

---

##The Application 
Tacitus was designed around the conceptual model described above.  It allows the user to easily capture pieces of the system as they arise.  Additionally, it graphically displays the system (either as lists or a network).  These displays are interactive, such that the user can interrogate the system to a level of detail that is appropriate for the user.

Tacitus was written in C++ using Microsoft Visual Studio 2013's Windows Form Template. It makes heavy use of Allegro 5, an open source gaming library (https://github.com/liballeg/allegro5).

Run the file "setup.exe" to load Tacitus on your machine.

---

##Questions, Comments, Concerns
Visit the [forum] (https://groups.google.com/forum/#!forum/tacitusopensource)

---

##Build Instructions

Using Microsoft Visual Studio 2013

1. Go to *File>New>Project*

2. In the New Project window under Templates, select *Visual C++>CLR*

3. In the adjacent field, select *CLR Empty Project*

4. Name the new project *knowledgeForm*

5. Press OK

6. Close Visual Studio

7. Copy and paste all files in the *source* folder of this repository to your newly created Visual Studio project folder.

	- the directory should be *...\knowledgeForm\knowledgeForm\*

	- you will be replacing two existing files (*knowledgeForm.vcxproj* and *knowledgeForm.vcxprj.filters*)

8. Restart Visual Studio and open the *knowledgeForm* project

9. Press *Ctrl+Shft+B* to build the solution

10. Using Windows Explorer, navigate to the folder that contains the newly created *knowledgeForm.exe* file created in step 9

11. Copy and paste all files in the *dependencies* folder of this repository to the folder opened in step 10

12. Double click *knowledgeFrom.exe* to run the program

13. Look at the [User's Guide] (https://github.com/aaronMcMahon/Tacitus/wiki/Users-Guide)

---

##About the Author
I am not a professional software developer.  I learned quite a bit from people on YouTube (especially *Jaime King*, *CodingMadeEasy*, and *What's a Creel?*).  With what I've learned, I am able to use these limited computer programming skills to solve real problems I have at work and home. I find it to be one of the most fulfilling experiences of my life.  I put Tacitus together about a year ago to help me keep my thoughts organized at work and am absolutely killing it.  I think Tacitus could be a lot better and am hoping to enlist the help of others to use and improve it.

