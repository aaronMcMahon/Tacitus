#include "myHeader.h"

void drawEdges(std::vector<Node> tempNodeVector, std::vector<Edge> tempEdgeVector, int translateX, int translateY)
{
/*
Give this function:
     - the node data
     - the edge data
     - how far the user has already panned the image in the x and y direction
And it will:
    - draw the edges on the map
*/
    translateX = -translateX;
	translateY = -translateY;
	int tempParentId = 0, tempChildId = 0, parentNodeAddress = 0, childNodeAddress = 0;
	float edgeLength, xParentScaled, yParentScaled, xChildScaled, yChildScaled, xParentRotated, yParentRotated, xChildRotated, yChildRotated, xParentTranslated, yParentTranslated, xChildTranslated, yChildTranslated, deltaX, deltaY;

	for (int i = 0; i < tempEdgeVector.size(); i++) //cycle through edges
	{
		tempParentId = tempEdgeVector[i].parent; //capture ID of parent node
		tempChildId = tempEdgeVector[i].child; //capture ID of child node
		for (int j = 0; j < tempNodeVector.size(); j++) //cycle through vectors
		{
			if (tempNodeVector[j].id == tempParentId) parentNodeAddress = j;
			if (tempNodeVector[j].id == tempChildId) childNodeAddress = j;
		}
		al_draw_line(translateX + tempNodeVector[parentNodeAddress].x + NODE_WIDTH / 2, translateY + tempNodeVector[parentNodeAddress].y + NODE_HEIGHT / 2, translateX + tempNodeVector[childNodeAddress].x + NODE_WIDTH / 2, translateY + tempNodeVector[childNodeAddress].y + NODE_HEIGHT / 2, EDGE_COLOR, EDGE_WIDTH);
		edgeLength = (tempNodeVector[parentNodeAddress].x - tempNodeVector[childNodeAddress].x) * (tempNodeVector[parentNodeAddress].x - tempNodeVector[childNodeAddress].x) + (tempNodeVector[parentNodeAddress].y - tempNodeVector[childNodeAddress].y) * (tempNodeVector[parentNodeAddress].y - tempNodeVector[childNodeAddress].y);
		edgeLength = sqrt(edgeLength);
		//scale arrow
		xParentScaled = (translateX + tempNodeVector[parentNodeAddress].x) * ARROW_SIZE / edgeLength;
		yParentScaled = (translateY + tempNodeVector[parentNodeAddress].y) * ARROW_SIZE / edgeLength;
		xChildScaled = (translateX + tempNodeVector[childNodeAddress].x) * ARROW_SIZE / edgeLength;
		yChildScaled = (translateY + tempNodeVector[childNodeAddress].y) * ARROW_SIZE / edgeLength;

		//rotate arrow
		xParentRotated = xParentScaled * cos(ARROW_RADIANS) + yParentScaled * -sin(ARROW_RADIANS);
		yParentRotated = xParentScaled * sin(ARROW_RADIANS) + yParentScaled * cos(ARROW_RADIANS);
		xChildRotated = xChildScaled * cos(ARROW_RADIANS) + yChildScaled * -sin(ARROW_RADIANS);
		yChildRotated = xChildScaled * sin(ARROW_RADIANS) + yChildScaled * cos(ARROW_RADIANS);

		//translate arrow
		deltaX = (translateX + tempNodeVector[childNodeAddress].x) - xChildRotated;
		deltaY = (translateY + tempNodeVector[childNodeAddress].y) - yChildRotated;
		xParentTranslated = xParentRotated + deltaX;
		yParentTranslated = yParentRotated + deltaY;
		xChildTranslated = xChildRotated + deltaX;
		yChildTranslated = yChildRotated + deltaY;

		//draw arrow
		al_draw_line(xParentTranslated + NODE_WIDTH / 2, yParentTranslated + NODE_HEIGHT / 2, xChildTranslated + NODE_WIDTH / 2, yChildTranslated + NODE_HEIGHT / 2, EDGE_COLOR, EDGE_WIDTH);
	}
}

void drawNodes(std::vector<Node> tempNodeVector, ALLEGRO_FONT *subFont, std::vector<Edge> tempEdgeVector, int translateX, int translateY)
{
/*
Give this function:
     - the node data
     - font for the text
     - the edge data
     - how far the user has already panned the image in the x and y direction
And it will:
    - draw nodes as colored boxes on the map
    - label those nodes using their nick name
*/	
    translateX = -translateX;
	translateY = -translateY;
	//ALLEGRO_FONT *subFont = al_load_font(FONT_TYPE, NODE_WIDTH, NULL); //create a font for Allegro Display
	for (int i = 0; i < tempNodeVector.size(); i++)
	{
		
		char const * nodeNickname = tempNodeVector[i].nickname.c_str();
		
		if (tempNodeVector[i].type == "Document")
		{
			int children = 0;
			//count children
			for (int j = 0; j < tempEdgeVector.size(); j++)
			{
				if (tempNodeVector[i].id == tempEdgeVector[j].parent) children++;
			}

			if (children > 0)
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(150, 150, 255));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}

			else
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(0, 0, 255));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}
		}
		else if (tempNodeVector[i].type == "Observation")
		{
			int children = 0;
			//count children
			for (int j = 0; j < tempEdgeVector.size(); j++)
			{
				if (tempNodeVector[i].id == tempEdgeVector[j].parent) children++;
			}
			
			if (children > 0)
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(255, 150, 150));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}

			else
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(255, 0, 0));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}			
		}
		else
		{
			int children = 0;
			//count children
			for (int j = 0; j < tempEdgeVector.size(); j++)
			{
				if (tempNodeVector[i].id == tempEdgeVector[j].parent) children++;
			}

			if (children > 0)
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(150, 255, 150));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}

			else
			{
				al_draw_filled_rectangle(translateX + tempNodeVector[i].x, translateY + tempNodeVector[i].y, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y + NODE_HEIGHT, al_map_rgb(34,177,76));
				al_draw_text(subFont, FONT_COLOR, translateX + tempNodeVector[i].x + NODE_WIDTH, translateY + tempNodeVector[i].y, 0, nodeNickname);
			}
		}
	}
}

void ExportNodesEdges(std::vector<Node> tempNodeVector, std::vector<Edge> tempEdgeVector, std::string nodeFileName, std::string edgeFileName)
{
/*
Give this function:
     - the node data
     - the edge data
     - the text file where node data saved
     - the text file where edge data saved
And it will:
    - overwrite the text files with updated data
*/	
	if (tempNodeVector.size() > 0)
	{
		std::ofstream nodeOutput;
		nodeOutput.open(nodeFileName);
		for (int i = 0; i < tempNodeVector.size() - 1; i++)
		{
			nodeOutput << tempNodeVector[i].id << "," << tempNodeVector[i].x << "," << tempNodeVector[i].y << "," << tempNodeVector[i].type << "," << tempNodeVector[i].nickname << "," << tempNodeVector[i].description << "," << tempNodeVector[i].fileLocation << "\n";
		}
		int i = tempNodeVector.size() - 1;
		nodeOutput << tempNodeVector[i].id << "," << tempNodeVector[i].x << "," << tempNodeVector[i].y << "," << tempNodeVector[i].type << "," << tempNodeVector[i].nickname << "," << tempNodeVector[i].description << "," << tempNodeVector[i].fileLocation;
		nodeOutput.close();

		if (tempEdgeVector.size() > 0)
		{
			std::ofstream edgeOutput;
			edgeOutput.open(edgeFileName);
			for (int i = 0; i < tempEdgeVector.size() - 1; i++)
			{
				edgeOutput << tempEdgeVector[i].parent << "," << tempEdgeVector[i].child << "," << tempEdgeVector[i].parentName << "," << tempEdgeVector[i].childName << "\n";
			}
			i = tempEdgeVector.size() - 1;
			edgeOutput << tempEdgeVector[i].parent << "," << tempEdgeVector[i].child << "," << tempEdgeVector[i].parentName << "," << tempEdgeVector[i].childName;
			edgeOutput.close();
		}
	}
}

Node addNode(std::vector<Node> &nodeVector, std::vector<Edge> &edgeVector, ALLEGRO_FONT *font, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT events, Node tempNode, int translateX, int translateY)
{
/*
Give this function:
     - the node data     
     - the edge data
     - font for the text
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - the data for a single node to be added
     - how far the user has already panned the image in the x and y direction
And it will:
    - return the data for the newly defined node

*/	
	tempNode.x = events.mouse.x + translateX;
	tempNode.y = events.mouse.y + translateY;

	if (nodeVector.size() > 0) tempNode.id = nodeVector[0].id + 1;
	else tempNode.id = 0;
	return tempNode;
}

Edge addEdge(std::vector<Node> &nodeVector, std::vector<Edge> &edgeVector, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT events, ALLEGRO_FONT * subFont, int translateX, int translateY)
{
/*
Give this function:
     - the node data     
     - the edge data
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - font for the text    
     - the data for a single node to be added
     - how far the user has already panned the image in the x and y direction
And it will:
    - wait for the user to click and drag between nodes to define an edge
    - check that the edge actually connects two nodes
    - return the data for the newly defined edge, if it is valid
*/

	int validEdge = 0;
	Edge tempEdge; //temporary edge object that will be added to vector of edges

	//wait for mouse button input
	while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		al_wait_for_event(event_queue, &events);
	}

	//collect input from mouse to establish a new edge object and add it to the vector of edges
	if (events.mouse.button & 1)
	{
		int tempX = events.mouse.x + translateX; //store x location of cursor when left mouse button pressed
		int tempY = events.mouse.y + translateY; //store y location of cursor when left mouse button pressed

		//cycle through the vector of nodes
		for (int i = 0; i < nodeVector.size(); i++)
		{
			//do this if an existing node was clicked
			if (tempX > nodeVector[i].x && tempX < nodeVector[i].x + NODE_WIDTH && tempY > nodeVector[i].y && tempY < nodeVector[i].y + NODE_HEIGHT)
			{
				validEdge++;
				tempEdge.parent = nodeVector[i].id; //store the clicked node's id as the parent id in the temporary edge object
				//al_wait_for_event(event_queue, &events);
				while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					al_clear_to_color(WINDOW_COLOR);
					al_draw_line(nodeVector[i].x - translateX, nodeVector[i].y - translateY, events.mouse.x, events.mouse.y, EDGE_COLOR, EDGE_WIDTH);
					//redrawNodesEdges(nodeVector, edgeVector);
					drawEdges(nodeVector, edgeVector, translateX, translateY);
					drawNodes(nodeVector, subFont, edgeVector, translateX, translateY);
					//drawMenu(0);
					al_flip_display();
					al_wait_for_event(event_queue, &events);
					tempX = events.mouse.x + translateX;
					tempY = events.mouse.y + translateY;
				}
				//cycle through the vector of nodes
				for (int j = 0; j < nodeVector.size(); j++)
				{
					//check if node sits under current location of cursor
					if (tempX > nodeVector[j].x && tempX < nodeVector[j].x + NODE_WIDTH && tempY > nodeVector[j].y && tempY < nodeVector[j].y + NODE_HEIGHT)
					{
						tempEdge.child = nodeVector[j].id; //store the identified node's as the parent id in the temporary edge object
						tempX = 0;
						tempY = 0;
						validEdge++;
					}
				}
			}
		}	
	}
	if (validEdge < 2)
	{
		tempEdge.parent = -1;
		tempEdge.child = -1;
	}
	return tempEdge;
}

std::vector<Node> moveChildren(std::vector<Node> nodeVector, std::vector<Edge> edgeVector, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT events, int translateX, int translateY)
{	
/*
Give this function:
     - the node data     
     - the edge data
     - font for the text
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - the data for a single node to be added
     - how far the user has already panned the image in the x and y direction
And it will:
    - change the location of a node and its children nodes on the map based on click-drag-release input from the user's mouse

*/
	int tempX, tempY, deltaX, deltaY; //integers to store coordinates of selected node and desired movement
	bool nodeActivated = false;
	std::vector<int> selectedNodes; //vector for storing id's of nodes to be moved

	while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		al_wait_for_event(event_queue, &events); //get input
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //if mouse button pressed, do this
		{
			if (events.mouse.button & 1) //make sure its the left mouse button that was pressed
			{
				//store the coordinates of the mouse cursor
				tempX = events.mouse.x + translateX;
				tempY = events.mouse.y + translateY;

				//check if there is a node at the stored coordinates
				for (int i = 0; i < nodeVector.size(); i++)
				{
					if (tempX > nodeVector[i].x && tempX < nodeVector[i].x + NODE_WIDTH && tempY > nodeVector[i].y && tempY < nodeVector[i].y + NODE_HEIGHT)
					{
						nodeActivated = true; //record that a node was clicked
						selectedNodes.push_back(nodeVector[i].id);//store the id of the clicked node in the vector of node id's to be moved
					}
				}
				if (nodeActivated == true)
				{
					//for the node that is clicked, add id's of its child nodes to the vector of node id's to be moved
					for (int i = 0; i < edgeVector.size(); i++)
					{
						if (edgeVector[i].parent == selectedNodes[0])
						{
							selectedNodes.push_back(edgeVector[i].child);
						}
					}
					nodeActivated = false;
				}
				while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP) al_wait_for_event(event_queue, &events); //wait until mouse button is released

				//calculated the delta of the x and y coordinates of position of mouse button down and mouse button up
				deltaX = events.mouse.x - tempX + translateX;
				deltaY = events.mouse.y - tempY + translateY;

				//add delta to coordinates of nodes whose id's are stored in the vector of node id's
				for (int i = 0; i < selectedNodes.size(); i++)
				{
					for (int j = 0; j < nodeVector.size(); j++)
					{
						if (nodeVector[j].id == selectedNodes[i])
						{
							nodeVector[j].x += deltaX;
							nodeVector[j].y += deltaY;
						}
					}
				}
			}
		}
	}
		

	return nodeVector;
}

void drawMenu(int i)
{
/*
Give this function:
     - integer value of zero*
And it will:
    - draw a list of key commands to the map
*I had a clever idea about using an integer to alter the list of commands, but gave up on it.  I never got around to dropping this functions requirement for an integer parameter

*/	
    
    ALLEGRO_FONT *menuFont = al_load_font(FONT_TYPE, FONT_SIZE, NULL); //create a font for Allegro Display
	int j = 0;
	const char * nKey = "Add Node = N";
	const char * eKey = "Add Edge = E";
	const char * leftControl = "Move Children = Left Control";
	const char * f1Key = "Save = F1";
	const char * deleteKey = "Delete Node = Delete";
	const char * backspaceKey = "Delete Edge = Backspace";
	const char * pKey = "Pan = P";

	if (i == 0 || i == 1)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, nKey);
		j++;
	}
	if (i == 0 || i == 2)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, eKey);
		j++;
	}
	if (i == 0 || i == 3)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, leftControl);
		j++;
	}
	if (i == 0 || i == 4)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, f1Key);
		j++;
	}
	if (i == 0 || i == 5)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, deleteKey);
		j++;
	}
	if (i == 0 || i == 6)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, backspaceKey);
		j++;
	}
	if (i == 0 || i == 7)
	{
		al_draw_text(menuFont, FONT_COLOR, WINDOW_X - MENU_X_OFFSET, FONT_SIZE + j * FONT_SIZE, 0, pKey);
		j++;
	}
}

std::vector<Node> deleteNode(std::vector<Node> &nodeVector, std::vector<Edge> &edgeVector, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT events, int translateX, int translateY)
{
/*
Give this function:
     - the node data     
     - the edge data
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - how far the user has already panned the image in the x and y direction
And it will:
    - check to see if the user just clicked a node on the map
    - if so, that node gets deleted from the node data

*/

	int tempX, tempY, deltaX, deltaY; //integers to store coordinates of selected node and desired movement
	bool nodeActivated = false;
	int selectedNode; //vector for storing id's of nodes to be moved

	while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		al_wait_for_event(event_queue, &events); //get input
		if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) //if mouse button pressed, do this
		{
			if (events.mouse.button & 1) //make sure its the left mouse button that was pressed
			{
				//store the coordinates of the mouse cursor
				tempX = events.mouse.x + translateX;
				tempY = events.mouse.y + translateY;

				//check if there is a node at the stored coordinates
				for (int i = 0; i < nodeVector.size(); i++)
				{
					if (tempX > nodeVector[i].x && tempX < nodeVector[i].x + NODE_WIDTH && tempY > nodeVector[i].y && tempY < nodeVector[i].y + NODE_HEIGHT)
					{
						nodeActivated = true; //record that a node was clicked
						selectedNode = i;//store the id of the clicked node in the vector of node id's to be moved					
					}
				}

				if (nodeActivated)
				{				
					//check for associated edges and delete
					for (int i = 0; i < edgeVector.size(); i++)
					{
						if (edgeVector[i].parent == nodeVector[selectedNode].id || edgeVector[i].child == nodeVector[selectedNode].id)
						{
							edgeVector.erase(edgeVector.begin() + i);
							i = -1;
						}
					}
					//erase selected node
					nodeVector.erase(nodeVector.begin() + selectedNode);
				}
			}
		}
	}


	return nodeVector;
}

std::vector<Edge> deleteEdge(std::vector<Node> &nodeVector, std::vector<Edge> &edgeVector, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT events, int translateX, int translateY)
{
/*
Give this function:
     - the node data     
     - the edge data
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - the data for a single node to be added
     - how far the user has already panned the image in the x and y direction
And it will:
    - check if the user clicks on a node, drags to another node and releases the mouse button
    - if that was done and edge will be created and added to the edge data

*/

	Edge tempEdge; //temporary edge object that will be deleted from vector of edges

	//wait for mouse button input
	while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	{
		al_wait_for_event(event_queue, &events);
	}

	//collect input from mouse to establish a new edge object and add it to the vector of edges
	if (events.mouse.button & 1)
	{
		int tempX = events.mouse.x + translateX; //store x location of cursor when left mouse button pressed
		int tempY = events.mouse.y + translateY; //store y location of cursor when left mouse button pressed

		//cycle through the vector of nodes
		for (int i = 0; i < nodeVector.size(); i++)
		{
			//do this if an existing node was clicked
			if (tempX > nodeVector[i].x && tempX < nodeVector[i].x + NODE_WIDTH && tempY > nodeVector[i].y && tempY < nodeVector[i].y + NODE_HEIGHT)
			{
				tempEdge.parent = nodeVector[i].id; //store the clicked node's id as the parent id in the temporary edge object
				//al_wait_for_event(event_queue, &events);
				while (events.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)
				{
					al_wait_for_event(event_queue, &events);
					tempX = events.mouse.x + translateX;
					tempY = events.mouse.y + translateY;
				}
				//cycle through the vector of nodes
				for (int j = 0; j < nodeVector.size(); j++)
				{
					//check if node sits under current location of cursor
					if (tempX > nodeVector[j].x && tempX < nodeVector[j].x + NODE_WIDTH && tempY > nodeVector[j].y && tempY < nodeVector[j].y + NODE_HEIGHT)
					{
						tempEdge.child = nodeVector[j].id; //store the identified node's id as the parent id in the temporary edge object
						tempX = 0;
						tempY = 0;
						for (int k = 0; k < edgeVector.size(); k++) //cycle throguh edge vector
						{
							//check if edge in edge vector at position k is same as temp edge
							if (tempEdge.parent == edgeVector[k].parent && tempEdge.child == edgeVector[k].child)
							{
								edgeVector.erase(edgeVector.begin() + k);
							}
						}
					}
				}
			}
		}
	}
	return edgeVector;
}
void highlightRelatives(int &activeNode, std::vector<Edge> &edgeVector, std::vector<Node> &nodeVector, int translateX, int translateY)
{
/*
Give this function:
     - data for one node (the active node)
     - the node data    
     - the edge data
     - font for the text
     - how far the user has already panned the image in the x and y direction
And it will:
    - draw a black boundary around all parent nodes of the active node
    - draw a yellow boundary around all child nodes of the active node

*/

	for (int i = 0; i < edgeVector.size(); i++)
	{
		if (edgeVector[i].parent == nodeVector[activeNode].id)
		{
			for (int j = 0; j < nodeVector.size(); j++)
			{
				if (nodeVector[j].id == edgeVector[i].child) al_draw_rectangle(nodeVector[j].x - translateX, nodeVector[j].y - translateY, nodeVector[j].x - translateX + NODE_WIDTH, nodeVector[j].y - translateY + NODE_WIDTH, al_map_rgb(255, 242, 0), HIGHLIGHT_WIDTH);
			}
		}
		if (edgeVector[i].child == nodeVector[activeNode].id)
		{
			for (int j = 0; j < nodeVector.size(); j++)
			{
				if (nodeVector[j].id == edgeVector[i].parent) al_draw_rectangle(nodeVector[j].x - translateX , nodeVector[j].y - translateY, nodeVector[j].x - translateX + NODE_WIDTH, nodeVector[j].y - translateY + NODE_WIDTH, al_map_rgb(0, 0, 0), HIGHLIGHT_WIDTH);
			}
		}
	}
}
void drawBackground(int translateX, int translateY)
{
/*
Give this function:
     - how far the user has already panned the image in the x and y direction
And it will:
    - draw a series of concentric circles to the map

*/	translateX = -translateX;
	translateY = -translateY;
	float maxRadius = WINDOW_X * WINDOW_X + WINDOW_Y * WINDOW_Y;
	maxRadius = sqrt(maxRadius);
	int colored = 0;
	for (float radius = maxRadius; radius > 0; radius = radius - maxRadius / DIVISIONS)
	{
		if (colored == 1)
		{
			al_draw_filled_circle(translateX, translateY + WINDOW_Y, radius, al_map_rgb(255, 255, 255));
			colored = 0;
		}
		else
		{
			al_draw_filled_circle(translateX, translateY + WINDOW_Y, radius, al_map_rgb(249, 242, 255));
			colored = 1;
		}
	}
}
void populateListNodeVector(std::vector<Node> &nodeVector, std::vector<Edge> &edgeVector, std::vector<Node> &listNodeVector)
{
/*
Give this function:
     - the node data     
     - the edge data
     - font for the text
     - an event queue that the Allegro library understands
     - an event that the Allegro library understands
     - the data for a single node to be added
     - how far the user has already panned the image in the x and y direction
And it will:
    - draw nodes in three lists based on type
	- nodes that have children will be drawn at the top, followed by nodes without children

*/

	int x = NODE_HEIGHT;
	int y = NODE_HEIGHT;
	int children = 0;
	Node nodeBuffer;
	for (int i = 0; i < nodeVector.size(); i++) //cycle through node vector
	{
		if (nodeVector[i].type == "Process") //check if node type is Process
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++; //cycle through edge vector.  if selected node id is found as a parent iterate children variable
			if (children > 0) //check if node has children
			{
				nodeBuffer = nodeVector[i]; //put node info into node buffer
				nodeBuffer.x = x; //update x coordinate
				nodeBuffer.y = y; //update y coordinate
				listNodeVector.push_back(nodeBuffer); //insert node buffer info into list node vector
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y; //shift y coordinate down the list
			}
			children = 0; //reset children
		}
	}
	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].type == "Process")
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++;
			if (children == 0)
			{
				nodeBuffer = nodeVector[i];
				nodeBuffer.x = x;
				nodeBuffer.y = y;
				listNodeVector.push_back(nodeBuffer);
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y;
			}
			children = 0;
		}
	}
	x = x + WINDOW_X / 6;
	y = NODE_HEIGHT;

	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].type == "Document" || nodeVector[i].type == "Data")
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++;
			if (children > 0)
			{
				nodeBuffer = nodeVector[i];
				nodeBuffer.x = x;
				nodeBuffer.y = y;
				listNodeVector.push_back(nodeBuffer);
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y;
			}
			children = 0;
		}
	}

	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].type == "Document" || nodeVector[i].type == "Data")
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++;
			if (children == 0)
			{
				nodeBuffer = nodeVector[i];
				nodeBuffer.x = x;
				nodeBuffer.y = y;
				listNodeVector.push_back(nodeBuffer);
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y;
			}
			children = 0;
		}
	}
	x = x + WINDOW_X / 6;
	y = NODE_HEIGHT;

	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].type == "Observation")
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++;
			if (children > 0)
			{
				nodeBuffer = nodeVector[i];
				nodeBuffer.x = x;
				nodeBuffer.y = y;
				listNodeVector.push_back(nodeBuffer);
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y;
			}
		}
		children = 0;
	}

	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].type == "Observation")
		{
			for (int j = 0; j < edgeVector.size(); j++) if (nodeVector[i].id == edgeVector[j].parent) children++;
			if (children == 0)
			{
				nodeBuffer = nodeVector[i];
				nodeBuffer.x = x;
				nodeBuffer.y = y;
				listNodeVector.push_back(nodeBuffer);
				y = NODE_HEIGHT * LIST_NODE_SCALAR + y;
			}
			children = 0;
		}
	}
}
void drawListDividers()
{
/*
Give this function:
- no parameters
And it will:
- draw lines across the List View window

*/
	al_draw_line(WINDOW_X / 2, 0, WINDOW_X / 2, WINDOW_Y, DIVIDER_COLOR, DIVIDER_THICKNESS);
	al_draw_line(WINDOW_X / 2, WINDOW_Y / 2 - FONT_SIZE * 3, WINDOW_X, WINDOW_Y / 2 - FONT_SIZE * 3, DIVIDER_COLOR, DIVIDER_THICKNESS);
	al_draw_line(WINDOW_X / 2, WINDOW_Y / 2 + FONT_SIZE * 3, WINDOW_X, WINDOW_Y / 2 + FONT_SIZE * 3, DIVIDER_COLOR, DIVIDER_THICKNESS);
}
void populateInterrogateNodeVector(std::vector<Node> &interrogateNodeVector, std::vector<Node> listNodeVector, std::vector<Edge> &edgeVector, int activeNode)
{
/*
Give this function:
- an empty vector to store node data
- the node data
- the edge data
- the location of a desired node within the node data
And it will:
- draw a duplicate of the desired node at the right/center of the List View window
- draw a duplicate of the desired nodes parent nodes at the right/top of the List View window
- draw a duplicate of the desired nodes child nodes at the right/bottom of the List View window
*/
	interrogateNodeVector.resize(0); //empty node vector
	Node nodeBuffer;// Node buffer
	nodeBuffer = listNodeVector[activeNode]; //active node passed into function goes into Node buffer
	nodeBuffer.x = WINDOW_X / 2 + NODE_WIDTH; //determine X coordinate of node
	nodeBuffer.y = WINDOW_Y / 2 - FONT_SIZE * 2; //determine Y coordinate of node
	interrogateNodeVector.push_back(nodeBuffer); //insert node buffer info into node vector

	int x = WINDOW_X / 2 + FONT_SIZE;
	int y = WINDOW_Y / 2 - FONT_SIZE * 4;
	int columnWidth = WINDOW_X / 6;
	int columnNumber = 0;

	for (int i = 0; i < edgeVector.size(); i++) //cycle through edge vector looking for children
	{
		if (interrogateNodeVector[0].id == edgeVector[i].parent) //check if parent id is same as id of node in 0 position of node vector
		{
			for (int j = 0; j < listNodeVector.size(); j++) //cycle through list node vector
			{
				if (listNodeVector[j].id == edgeVector[i].child) //check if id of node is same as child id in edge vector
				{
					nodeBuffer = listNodeVector[j];
					nodeBuffer.x = x;
					nodeBuffer.y = y;
					y = y - NODE_HEIGHT * LIST_NODE_SCALAR;
					if (y < 0)
					{
						columnNumber++;
						x = WINDOW_X / 2 + FONT_SIZE + columnNumber * columnWidth;
						y = WINDOW_Y / 2 - FONT_SIZE * 4;

					}
					interrogateNodeVector.push_back(nodeBuffer);
				}
			}
		}
	}

	x = WINDOW_X / 2 + FONT_SIZE;
	y = WINDOW_Y / 2 + FONT_SIZE * 4;
	columnNumber = 0;

	for (int k = 0; k < edgeVector.size(); k++) //cycle through edge vector looking for parent
	{
		if (interrogateNodeVector[0].id == edgeVector[k].child)
		{
			for (int l = 0; l < listNodeVector.size(); l++)
			{
				if (listNodeVector[l].id == edgeVector[k].parent)
				{
					nodeBuffer = listNodeVector[l];
					nodeBuffer.x = x;
					nodeBuffer.y = y;
					y = y + NODE_HEIGHT * LIST_NODE_SCALAR;
					if (y > WINDOW_Y)
					{
						columnNumber++;
						x = WINDOW_X / 2 + FONT_SIZE + columnNumber * columnWidth;
						y = WINDOW_Y / 2 + FONT_SIZE * 4;
					}
					interrogateNodeVector.push_back(nodeBuffer);
				}
			}
		}
	}
}
