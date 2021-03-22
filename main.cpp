#include "Special_Node.h"
#include "ConsoleScreen.h"
#include "Snake.h"
#include "Food.h"


bool escaped_pressed()
{
	return (bool)(GetAsyncKeyState((unsigned short)27) & 0x8000); // Escape
	
}

std::vector<Position> Astar_alg(const Node& start, const Node& end, ConsoleScreen& console_screen)
{

	Special_Node::Table table;
	auto set_ID_fromNode = [&table](const Special_Node& node) {

		if (node.console_screen.get_value(node.pos.x, node.pos.y) == Food::sign || 
			node.console_screen.get_value(node.pos.x, node.pos.y) == ' ' 
			)
		{
			table[node.getID()].push_back(std::make_unique<Special_Node>(node));
		}

	};
	set_ID_fromNode(Special_Node(start, console_screen));
	set_ID_fromNode(Special_Node(end, console_screen));
	auto it0 = table.find(Special_Node(start, console_screen).getID());
	if (table.end() == it0)
		return std::vector<Position>{};
	auto it1 = table.find(Special_Node(end, console_screen).getID());
	if (table.end() == it1)
		return std::vector<Position>{};
	Special_Node* act_start = it0->second.front().get();
	Special_Node* act_end = it1->second.front().get();

	act_start->fScore = start.pos.get_distance(end.pos);
	act_start->gScore = 0;

	std::vector<Special_Node*> priority_list;

	auto comparsion = [](const Special_Node* a, const Special_Node* b) { return a->fScore > b->fScore; };
	priority_list.push_back(act_start);

	while (!priority_list.empty())
	{
		Special_Node* act_node = priority_list.front();
		act_node->finished = true;
		std::pop_heap(priority_list.begin(), priority_list.end(), comparsion); priority_list.pop_back(); // remove the element with the lowest fScore

		if (act_node->pos == act_end->pos)
		{
			break;
		}


		for (auto neighbour : act_node->neighbours(table))
		{
			if (neighbour->finished)
				continue;

			float distance_neighbour_actnode = act_node->pos.get_distance(neighbour->pos);
			float g_actnode_plus_dist = act_node->gScore + distance_neighbour_actnode;
			bool node_is_already_in_list = std::find(priority_list.begin(), priority_list.end(), neighbour) != priority_list.end();
			if (node_is_already_in_list && g_actnode_plus_dist >= neighbour->gScore)
				continue;
			
			neighbour->parent = act_node;
			neighbour->gScore = g_actnode_plus_dist;
			neighbour->fScore = neighbour->gScore + neighbour->pos.get_distance(end.pos);

			if (!node_is_already_in_list)
			{
				priority_list.push_back(neighbour);
			}
		}
		std::make_heap(priority_list.begin(), priority_list.end(), comparsion);




	}
	return [&]()
	{
		std::vector<Position> path;
		Node* parent = act_end->parent;
		if (parent == nullptr)
		{
			//std::cout << "No path is found! \n"; ///< Error Message
			return path;
		}
		path.push_back(end.pos);
		Position start1 = start.pos;
		while (parent != nullptr)
		{
			Position act_pos = parent->pos;
			if (!(parent->pos == start1))
			{
				path.push_back(act_pos);

			}

			parent = parent->parent;
		}
		//path.push_back(start.pos);
		return path;
	}();




}

int main()
{
	ConsoleScreen console_screen;
	Head snake;
	Food food;
	std::vector<Position> path;
	console_screen.init_map();
	bool lose = false;
	food.spawn();
	console_screen.set_map(food.pos_x, food.pos_y, food.sign);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	while (!escaped_pressed() && !lose)
	{
		//snake.update_direction(); < User Control
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		if (elapsed_seconds.count() > 0.1)  
		{
			lose = snake.check_lose();
			if (lose)
			{
				Sleep(10e3);
			}
			food.set_on_map(console_screen);
			snake.eat(food);
			start = std::chrono::system_clock::now();
			snake.set_on_map(console_screen);
			console_screen.draw();
			if (path.empty())
			{

				Node head;
				head.pos.x = snake.pos_x;
				head.pos.y = snake.pos_y;
				switch (snake.direction)
				{
				case UP:
					head.pos.y -= 1;
					break;
				case DOWN:
					head.pos.y += 1;
					break;
				case RIGHT:
					head.pos.x += 1;
					break;
				case LEFT:
					head.pos.x -= 1;
					break;
				default:
					break;
				}
				Node goal;
				goal.pos.x = food.pos_x;
				goal.pos.y = food.pos_y;
				path = Astar_alg(head, goal, console_screen);
			}
			else
			{
				snake.control(path);
				path.pop_back();
			}
			
		}

	}
	if (lose)
		std::cout << "You lose!\n";
	
	return 0;
}