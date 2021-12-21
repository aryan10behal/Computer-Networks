#include <vector>
#include "node.h"
#include <iostream>
#include <string>

using namespace std;

void printRT(vector<RoutingNode*> nd){
/*Print routing table entries*/
	for (int i = 0; i < nd.size(); i++) {
	  nd[i]->printTable();
	}
}


bool compare_struct(struct routingtbl a,struct routingtbl b)
{
	if(a.tbl.size() == 0)
		return false;
	if(a.tbl.size() != b.tbl.size())
		return false;
	for(int i = 0;i<a.tbl.size();i++)
	{
		if(!( (a.tbl[i].dstip.compare(b.tbl[i].dstip) == 0)  && (a.tbl[i].nexthop.compare(b.tbl[i].nexthop) == 0) && (a.tbl[i].ip_interface.compare(b.tbl[i].ip_interface) == 0) && (a.tbl[i].cost == b.tbl[i].cost)))
			return false;
	}
	return true;
}
void routingAlgo(vector<RoutingNode*> nd)
{
	
	while(true)
	{
		// creating a copy of old version of routing tables
		vector<routingtbl> old_tables;
		for(int i= 0;i<nd.size();i++)
			old_tables.push_back(nd[i]->getTable());

		for(int i=0;i<nd.size();i++)
			nd[i]->sendMsg();
		bool converged = true;
		for(int i=0;i<nd.size();i++)
		{
			//comparing newly updated routing tables with older copy to check convergence...
			if(!compare_struct(old_tables[i],nd[i]->getTable()))
				converged = false;
		}
		if(converged)
		{
			cout<<"converged... breaking out of the loop\n";
			break;
		}
		else
			{
			cout<<"Didnt converge yet..\n";
			printRT(nd);
			}
	}
	cout<<" Done with Q1\n\n Showing output..\n\n";
}

void RoutingNode::recvMsg(RouteMsg *msg) 
{
	for(int i=0;i<msg->mytbl->tbl.size();i++)
	{
		int ind=-1;
		for(int j=0;j<mytbl.tbl.size();j++)
		{
			if(mytbl.tbl[j].dstip==msg->mytbl->tbl[i].dstip)
			{
				ind = j;
				break;
			}
		}

		// if routing table of sender not found, then a new entry is made.. Else we try to update value of cost
		if(ind!=-1)
		{
			// updating cost in routing table..
			if(mytbl.tbl[ind].cost > msg->mytbl->tbl[i].cost+1 || mytbl.tbl[ind].nexthop==msg->from)
				{
					mytbl.tbl[ind].cost=msg->mytbl->tbl[i].cost+1;
					mytbl.tbl[ind].nexthop = msg->from;
				}
		}
		else
		{
			RoutingEntry new_route;
			new_route.ip_interface= msg->recvip;
			new_route.nexthop=msg->from;
			new_route.dstip=msg->mytbl->tbl[i].dstip;
			if(msg->from==new_route.dstip)
			{
				new_route.cost=1;
			}
			else
				new_route.cost=1+msg->mytbl->tbl[i].cost;
			mytbl.tbl.push_back(new_route);
		}
	}
}
