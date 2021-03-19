
#include "../header/node.h"
//node
void node::show_list()const
{
    for(node*ptr = next;ptr;ptr=ptr->next)
        cout<<ptr->get_val()<<" ";
}

