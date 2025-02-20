#include "tree.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GRN   "\x1B[32m"

int max(int a, int b)
{
    int res = a;
    if (b > a)
        res = b;
    return res;
}

node* create_tree(int value)
{
    node* root = (node*) calloc(1, sizeof(node)); // if 0
    
    root->value_        = value;
    root->height_       =     0;  
    root->total_height_ =     0;

    return root;
}

void chop_tree(node* root)
{
    if (root->left_)
        chop_tree(root->left_);

    if (root->right_)
        chop_tree(root->right_);

    if (root->parent_)
    {
        if (root->is_right_)
        {
            root->parent_->right_ = NULL;
        }
        else
        {
            root->parent_->right_ = NULL;
        }
    root->parent_ = NULL;
    }    
    
    free(root);

}

node* insert(node** root, int value)
{
    //printf("inserting started \n");
    if (!*root)
    {
        printf("Your ptr is NULL, I'm sending it back \n");
        return NULL;
    }

    node* old_parent = *root;

    node* son = (node*) malloc(sizeof(node));

    if (!son)
    {
        printf("problems with memory allocation \n");
        return NULL;
    }
                                              
    while (1)
    {
        if (value == old_parent->value_)
        {
            printf(RED "HIT\n" RESET);
            return old_parent;  
        }
                                                   
        if (value < old_parent->value_)
        {
            if (!old_parent->left_)
            {
                son->left_         =                      NULL;
                son->right_        =                      NULL;
                son->parent_       =                old_parent;
                son->value_        =                     value;
                son-> left_height_ =                         0;
                son->right_height_ =                         0;
                son->total_height_ =    (*root)->total_height_;
                son->height_       = old_parent->height_   - 1;
                son->position_     = old_parent->position_ * 2;
                son->is_right_     =                     false;

                
                old_parent->left_ = son;
                break;
            }

            old_parent = old_parent->left_;
        }
        else
        {
            if (!old_parent->right_)
            {
                son->left_         =                          NULL;
                son->right_        =                          NULL;
                son->parent_       =                    old_parent;
                son->value_        =                         value;
                son-> left_height_ =                             0;
                son->right_height_ =                             0;
                son->total_height_ =        (*root)->total_height_;
                son->height_       = old_parent->height_       - 1;
                son->position_     = old_parent->position_ * 2 + 1;
                son->is_right_     =                          true;

                old_parent->right_ = son;
                break;
            }

            old_parent = old_parent->right_;
        }
        
    }

    //printf("beda \n");
    
    node* problem_leave = raise_part_heights(son);   /// all this might be simplified

    if (problem_leave)
    {
        //printf("problem in %d \n", problem_leave->value_);
        node* parent = problem_leave->parent_;                                                     
        bool is_right = problem_leave->is_right_;
        node* new_leave = balance(problem_leave);




        if (!parent) 
        {
            *root = new_leave;
        }
        else if (is_right)
        {
            parent->right_ = new_leave;
        }
        else
        {
            parent->left_  = new_leave;
        }
    
        return son;
    } 
    
    if (son->height_ < 0)
        raise_heights(*root, 2);

    return son;

#if 0 
        printf("new_leave = %d, new->left = %d, new->right = %d, left_parent = %d, right_parent = %d \n", new_leave->value_, new_leave->left_->value_, new_leave->right_->value_, new_leave->left_->parent_->value_, new_leave->right_->parent_->value_);

        
        if (!new_leave->is_right_)
            printf("new is left \n");

        if (!new_leave->left_->is_right_)
            printf("left is left \n");


        if (new_leave->parent_)
        {
            printf("par = %d \n", new_leave->parent_->value_);
            if (new_leave->parent_->right_)
                printf("par->left = %d \n", new_leave->parent_->right_->value_);
        }
#endif  // for checkings
}


#if 0
node* rem_leave(node** tree, int value)  // returns pointer to the new leave on the old place
                                        // recalc heights and positions and
                                        // left/right   l/r heights 
{
    node* old_leave = is_in_tree(*tree, value);

    if (!old_leave)
    {
        printf("There is no %d in the tree \n", value);
        return NULL;
    }

    if (old_leave->value_ == (*tree)->value_)
    {
        printf("I will not destroy the root, too long to change the function \n");
        return NULL;
    }

    node* parent      = old_leave->parent_;
    bool old_is_right = old_leave->is_right_;

    node* new_leave;

    if (!old_leave->left_)
    {
        if (!old_leave->right_) // works ok
        {
            // *************************************************************************
            if (!parent)
            {
                printf("it is the last leave, i will not harm it \n");
                return NULL;
            }
            node* problem_leave;

            if (old_is_right)        
            {
                printf("old = %d,  \n", old_leave->value_);
                parent->right_ = NULL;
                problem_leave = decrease_part_heights(parent);
            }
            else
            {
                parent->left_ = NULL;
                problem_leave = decrease_part_heights(parent);
            }

            printf("wats wrong \n");
            move_flying_tree(*tree);
    
            printf("heyyyyyyy 1\n \n");
            if (problem_leave)
            {
            printf("hihest balanced \n");
            printf("problem in %d \n", problem_leave->value_);
            node* new_parent = problem_leave->parent_;                                                     
            printf("problem parent =  %d \n", new_parent->value_);
            bool is_right = problem_leave->is_right_;
            node* final_leave = balance(problem_leave);
            printf("balanced \n");

        
            if (!new_parent)
            {    
                *tree = new_leave;
                printf("local root changed \n");
            }
            else if (is_right)
            {
                new_parent->right_ = final_leave;
            }
            else
            {
                new_parent->left_  = final_leave;
            }
                printf("balanced \n");
            }

            printf("heyyyyyyy 2\n \n");
            old_leave->parent_ = NULL;
            old_leave->right_  = NULL;
            free(old_leave);

            //check_heights(tree);
            return NULL;
        }
       // **********************************************************************************
       // here  if there is right son. tree is balanced -> son has no children
       // **********************************************************************************
       // seems to work

        new_leave = old_leave->right_;
        new_leave->parent_ = parent;
        //new_leave->right_ = old_leave->right_;
        new_leave->position_ = old_leave->position_;
        new_leave->height_++;

        if (old_is_right)
        {
            parent->right_ = new_leave; // is right = true as before, as after
            parent->right_height_--;
            printf("im here \n");

        }
        else
        {
            parent->left_  = new_leave;
            new_leave->is_right_ = false;
            parent->left_height_--;
        }

        printf("old leeave = %d, parent = %d, new_leave = %d \n", old_leave->value_, parent->value_, new_leave->value_);


    move_flying_tree(*tree);
    

    if (old_leave->parent_)
    {
        printf("old leave par = %d\n", old_leave->parent_->value_);
    }
    node* problem_leave = check_part_heights(old_leave->parent_);   /// 

    if (problem_leave)
    {
        printf("hihest balanced \n");
        printf("problem in %d \n", problem_leave->value_);
        node* new_parent = problem_leave->parent_;                                                     
        printf("problem parent =  %d \n", new_parent->value_);
        bool is_right = problem_leave->is_right_;
        node* final_leave = balance(problem_leave);
        printf("balanced \n");

    
        if (!new_parent)
        {    
            *tree = new_leave;
            printf("local root changed \n");
        }
        else if (is_right)
        {
            new_parent->right_ = final_leave;
        }
        else
        {
            new_parent->left_  = final_leave;
        }
        printf("balanced \n");
    }
    old_leave->parent_ = NULL;
    old_leave->right_  = NULL;
    free(old_leave);

    return new_leave;
    // **********************************************************************************
    }

    // **********************************************************************************
    // both cildren

    printf("both children \n \n");

    new_leave = max_leave(old_leave->left_); // must be always right except for case only one left son
    int new_l_pos = new_leave->position_;
    new_leave->position_ = old_leave->position_;                                            
    new_leave->height_   = old_leave->height_;
    node* old_parent_    = new_leave->parent_;
    node* problem_leave;
    // add count of left right heiights TODO 
    // CHILDREN OF MAX_LEFT

    new_leave->right_height_ = old_leave->right_height_;  // delete the same in the end

    printf("new_l = %d \n", new_leave->value_);

    ///  * * ** ** * ** * * **  ** * * * *  * ** * * * * *   calculation of
    //right/left heights
    node* cur_leave = new_leave;



    if ( --(cur_leave->parent_->right_height_) == cur_leave->parent_->left_height_)
    {
        cur_leave = cur_leave->parent_;
        while (cur_leave != old_leave) //left height of new leave
        {
            if (cur_leave->is_right_)
            {
                cur_leave->parent_->right_height_--;
                cur_leave = cur_leave->parent_;
                continue;
            }

            cur_leave->parent_->left_height_--;
            cur_leave = cur_leave->parent_;
        }                                       
    }                 // not tested yet

    if (cur_leave->parent_->right_height_ < 0)   /// if old_leave == new_leave->parent
        cur_leave->parent_->right_height_++;



    ///  * * ** ** * ** * * **  ** * * * *  * ** * * * * *
    //works with son of new leave
    if (new_leave->left_)
    {   
        if  (old_parent__ == old_leave)
        {
            printf("new->parent = old leave \n");
            if (parent)
            {
                if (old_is_right)
                {
                    parent->right_ = new_leave;
                }
                else
                {
                    parent->left_  = new_leave;
                }
                
            }
            new_leave->parent_ = parent; // out of if, cause null is also suitable

            recalc_positions(new_leave);
#if 0
            new_leave->left_->height_++;
            new_leave->left_->position_ = new_l_pos;
#endif
      

    //        printf("new_l_position = %d \n", new_l_pos);
            new_leave->is_right_ = old_is_right;
            new_leave->right_ = old_leave->right_;
            old_leave->right_->parent_ = new_leave;
            move_flying_tree(*tree);

            node* problem_leave = check_part_heights(old_parent_);   /// 



            if (problem_leave)
            {
                printf(" upper balanced \n");
                printf("problem in %d \n", problem_leave->value_);
                node* new_parent = problem_leave->parent_;                                                     
                bool is_right = problem_leave->is_right_;
                node* final_leave = balance(problem_leave);
                printf("balanced \n");

            
                if (new_parent == *tree)
                {
                    *tree = new_leave;
                    printf("root changed \n");
                }
                else if (!new_parent)
                {    
                    new_parent = new_leave;
                    printf("local root changed \n");
                }
                else if (is_right)
                {
                    new_parent->right_ = final_leave;
                }
                else
                {
                    new_parent->left_  = final_leave;
                }
                printf("balanced \n");
            }
            return new_leave; 

            //new_leave->right_ = new_leave->left_;  seems pointless
            //new_leave->right_->is_right_ = true;
           // new_leave->left_ = NULL;  // for case of mistake anywhere next
        }
        else
        {
            old_parent_->right_  = new_leave->  left_;
            new_leave->left_->position_ = new_l_pos;
            new_leave->left_->is_right_ = true;
            //heights
            new_leave->left_->parent_   = old_parent_;

            raise_heights(new_leave->left_, 1);
            problem_leave = decrease_part_heights(new_leave->left_);  // not checked
    
        }

        // balance
    }
   
#if 0
    ///  * * ** ** * ** * * **  ** * * * *  * ** * * * * *  
    if (new_leave->is_right_)
    {
       // new_leave->parent_->right_height_--;  //rl h control

        new_leave->parent_->right_ = NULL;
    }
    else //// /                                  fignya
    {
        //new_leave->parent_->left_height_--;  // initially was only height
        new_leave->parent_->left_ = NULL; // left/right

    }
    printf("after cycle \n");
#endif  /// seems bred


    if (parent)
    {
        if (old_is_right)
        {
            parent->right_ = new_leave;
        }
        else
        {
            parent->left_  = new_leave;
        }
    }

    printf("afsafAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA \n");
//    printf("parent = %d \n", parent->value_);

    new_leave->parent_ = parent;


#if 0
    if (new_leave->parent_ != old_leave)
    {
        new_leave->left_  = old_leave-> left_;
    }
#endif // semms imposible 

    new_leave->right_ = old_leave->right_;

    printf("new_leave = %d \n", new_leave->value_);

    if (new_leave->left_)  // l/r heights ********************************************************
    {
        new_leave->left_->parent_ = new_leave;
        new_leave-> left_height_ = 1 + max(new_leave-> left_->left_height_, new_leave-> left_->right_height_);
        printf("ale left \n");
    }
    else
    {
        new_leave->left_height_ = 0;
    }

    if (new_leave->right_)
    {
        new_leave->right_->parent_ = new_leave;
        new_leave->right_height_ = 1 + max(new_leave->right_->left_height_, new_leave->right_->right_height_);
        printf("ale right \n");
    }
    else
    {
        new_leave->right_height_ = 0;
    }
    

    if (old_parent_->left_)
    {
        old_parent_->left_height_ = 1 + max(old_parent_->left_->left_height_, old_parent_->left_->right_height_);
        printf("old ale left \n");
    }
    else
    {
        old_parent_->left_height_ = 0;
    }
    
    if (old_parent_->right_)
    {
        old_parent_->right_height_ = 1 + max(old_parent_->right_->right_height_, old_parent_->right_->left_height_);
        printf("old ale right \n");
    }
    else
    {
        old_parent_->left_height_ = 0;
    }
    //********************************************************************************************

 //   printf("parent->left = %d, new_leave->par = %d \n", parent->left_->value_, new_leave->parent_->value_);

    new_leave->is_right_ = old_is_right;

    move_flying_tree(*tree);
    
    problem_leave = decrease_part_heights(old_parent_);   /// 



    if (problem_leave)
    {

        printf("before balanced \n");
        printf("problem in %d \n", problem_leave->value_);
        node* new_parent = problem_leave->parent_;                                                     
        bool is_right = problem_leave->is_right_;
        node* final_leave = balance(problem_leave);
        printf("balanced \n");

    
        if (new_parent == *tree)
        {
            *tree = new_leave;
            printf("root changed \n");
        }
        else if (!new_parent)
        {    
            new_parent = new_leave;
            printf("local root changed \n");
        }
        else if (is_right)
        {
            new_parent->right_ = final_leave;
        }
        else
        {
            new_parent->left_  = final_leave;
        }
        printf("balanced \n");
    }

    return new_leave; // not sure, some data lost
}
#endif

int move_flying_tree(node* root)
{
    int o_leaves = 0;
    node* it = tree_begin(root);
    while(it)
    {
        if (it->height_ == 0)
        {
            o_leaves++;
            break;
        }
        it = inc(it);
    }

    if (o_leaves == 0)
    {
        decrease_heights(root);    
        dec_max_h(root);
        printf("all heights are decreased \n");

    }

    return o_leaves;
}  

node* max_leave(node* root)
{
    node* max_leave = root;

    while(max_leave->right_)
    {
        max_leave = max_leave->right_;
    }

    return max_leave;
}

node* min_leave(node* root)
{
    node* min_leave = root;


    while(min_leave->left_)
    {
        min_leave = min_leave->left_;
    }

    return min_leave;
}

void print_tree(node* root)
{
    if (!root) return;

    if (root->left_) 
    {
        print_tree(root->left_);
    }
    
    if (root->right_)
    {
        print_tree(root->right_);
    }

    printf("%d \n", root->value_);

}


node* is_in_tree(node* root, int value) ///NULL if no, pointer if yes/////// node + node->left
{
    if (root == NULL)
    {
        return NULL;
    }

    node* to_find = NULL;
    if (root->value_ == value)
        return root;



    if (value < root->value_)
    {
        if (root->left_)
            return is_in_tree(root->left_, value);

        return NULL;
    }

    if (root->right_)
        return is_in_tree(root->right_, value); 

    return NULL;

}


//  better redo without recursion
int raise_heights(node* root, int param_one)  /// height++ in the whole tree,  if param = 1, total height not touched, if 2, touched
{
    if (!root) 
        return 0;


    if (root->left_) 
    {
        raise_heights(root->left_, param_one);
    }
    
    if (root->right_)
    {
        raise_heights(root->right_, param_one);
    }
    
    root->height_++;

    if (param_one == 2)
        root->total_height_++;

    return root->height_;
}

int decrease_heights(node* root)  /// height-- in the whole tree under the mentioned root
{
    if (!root) 
        return 0;

    if (root->left_) 
    {
        decrease_heights(root->left_);
    }
    
    if (root->right_)
    {
        decrease_heights(root->right_);
    }
    
    root->height_--;

    return root->height_;
}

int dec_max_h(node* root)
{

    if (!root) 
        return 0;

    if (root->left_) 
    {
        dec_max_h(root->left_);
    }
    
    if (root->right_)
    {
        dec_max_h(root->right_);
    }
    
    root->total_height_--;

    if (root->total_height_ < 0)
    {
        printf("max_h < 0, beda \n");
        return -1;
    }

    return root->total_height_;
}

node* raise_part_heights(node* new_leave) // returns NULL if no balancing needed
{
    node* cur_leave = new_leave;

    while(cur_leave->parent_)
    {
        if (cur_leave->is_right_)
        {
            cur_leave->parent_->right_height_++;
            if (cur_leave->parent_->right_height_ <= cur_leave->parent_->left_height_)
                break;
        }
        else
        {
            cur_leave->parent_->left_height_++;
            if (cur_leave->parent_->right_height_ >= cur_leave->parent_->left_height_)
                break;
        }

#if 0       
        //printf("par_right_tree = %d, par_left = %d. par_val = %d \n", cur_leave->parent_->right_height_, cur_leave->parent_->left_height_, cur_leave->parent_->value_);

        //printf("tree_dif = %d \n", abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_));
#endif  // for additional checking


        if (abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_) >= 2)
            return cur_leave->parent_;
        
        cur_leave = cur_leave->parent_;
    }
    return NULL;
}


#if 0
node* decrease_part_heights(node* new_leave) // returns NULL if no balancing needed
{
    node* cur_leave = new_leave;


    if (cur_leave->is_right_)
    {
        cur_leave->parent_->right_height_--;
        if (cur_leave->parent_->right_height_ >= cur_leave->parent_->left_height_)
            break;
    }
    else
    {
        cur_leave->parent_->left_height_--;
        if (cur_leave->parent_->right_height_ <= cur_leave->parent_->left_height_)
            break;
    }

    if (abs(cur_leave->right_height_ - cur_leave->left_height_) >= 2)
        return cur_leave;
   
    while(cur_leave->parent_)
    {
        if (cur_leave->is_right_)
        {
            cur_leave->parent_->right_height_--;
            if (cur_leave->parent_->right_height_ >= cur_leave->parent_->left_height_)
                break;
        }
        else
        {
            cur_leave->parent_->left_height_--;
            if (cur_leave->parent_->right_height_ <= cur_leave->parent_->left_height_)
                break;
        }



#if 0       
        //printf("par_right_tree = %d, par_left = %d. par_val = %d \n", cur_leave->parent_->right_height_, cur_leave->parent_->left_height_, cur_leave->parent_->value_);

        //printf("tree_dif = %d \n", abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_));
#endif  // for additional checking


        if (abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_) >= 2)
            return cur_leave->parent_;
        
        cur_leave = cur_leave->parent_;
    }
    return NULL;
}
#endif // whole func


node* check_part_heights(node* deleted_par) // returns NULL if no balancing needed
{
    printf("check part \n");
    node* cur_leave = deleted_par;
    
    if (!cur_leave)
        printf("no deleted par \n");

    printf("curval = %d , left_h = %d, r_h = %d \n", cur_leave->value_, cur_leave->left_height_, cur_leave->right_height_);
    printf("line = %d\n", __LINE__);

    if (abs(cur_leave->right_height_ - cur_leave->left_height_) >= 2) // possible to put inside
        return cur_leave;
    printf("line = %d\n", __LINE__);

    //node* cur_leave = new_leave;

    while(cur_leave->parent_)
    {

#if 0       
        //printf("par_right_tree = %d, par_left = %d. par_val = %d \n", cur_leave->parent_->right_height_, cur_leave->parent_->left_height_, cur_leave->parent_->value_);

        //printf("tree_dif = %d \n", abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_));
#endif  // for additional checking


    if (abs(cur_leave->parent_->right_height_ - cur_leave->parent_->left_height_) >= 2)
        return cur_leave->parent_;
        
        cur_leave = cur_leave->parent_;
    }  // higher checked
    return NULL;
}

node* balance(node* root)  // returns new root of the given subtree
{
    if (root->left_height_ < root->right_height_)
    {
        printf("left \n");
        if (root->right_->left_height_ <= root->right_->right_height_)
        {
            return left_small_turn(root);
        }
        return left_big_turn(root);
    }

    if (root->left_->right_height_ <= root->left_->left_height_)
        return right_small_turn(root);

    printf("right big \n");
    return right_big_turn(root);
}


node* left_small_turn(node* root)
{
    printf("left small root = %d \n", root->value_);
    node* pre_root = NULL;
    bool root_is_right = false;
    if (root->parent_)
    {
        pre_root = root->parent_;
        root_is_right = root->is_right_;
    }

    int root_pos = root->position_;
    node* new_root = root->right_;

    new_root->parent_ = pre_root;
    new_root->is_right_ = root_is_right;


    if (root->right_->left_)
    {
        root->right_->left_->parent_ = root;
    }
    

    root->right_   = root->right_->left_;
    new_root->left_ = root;
    root->parent_ = new_root;

    decrease_heights(root->left_);
    root->height_--;

    raise_heights(new_root->right_, 1);
    new_root->height_++;

    new_root->right_->is_right_ = true;
    new_root->left_height_++;

    root->right_height_ = root->left_height_;
    root->is_right_ = false; // might break smth

    if (root->right_)
        root->right_->is_right_ = true;

    
    new_root->position_ = root_pos;
    if (!recalc_positions(new_root))
        return NULL;

#if 0 
/*
    printf("for 6: h = %d  l_h = %d, r_h = %d, pos = %d \n", root->height_, root->left_height_, root->right_height_, root->position_);
    printf("for 7: h = %d  l_h = %d, r_h = %d, pos = %d \n", new_root->height_, new_root->left_height_, new_root->right_height_, new_root->position_);
    printf("for 8: h = %d  l_h = %d, r_h = %d, pos = %d \n", new_root->right_->height_, new_root->right_->left_height_, new_root->right_->right_height_, new_root->right_->position_);
    */
#endif  // extra checks

    return new_root;
}

node* left_big_turn(node* root)
{
    node* pre_root = NULL;
    bool root_is_right = false;

    int root_pos = root->position_;

    node* new_root = root->right_->left_;

    if (root->parent_)
    {
        pre_root = root->parent_;
        root_is_right = root->is_right_;
    }



    if (new_root->left_)
        new_root->left_->parent_ = root;
    root->right_ = new_root->left_;



    if (new_root->right_)
        new_root->right_->parent_ = new_root->parent_;
    new_root->parent_->left_ = new_root->right_;

    

    if (root->right_)
        root->right_->is_right_ = true;


    if (new_root->parent_->left_)
        new_root->parent_->left_->is_right_ = false;


    
    new_root->left_ = root;
    new_root->left_->parent_ = new_root;
    
    new_root->right_ = new_root->parent_;
    new_root->right_->parent_ = new_root;

    new_root->parent_ = pre_root;
    new_root->is_right_ = root_is_right;

    raise_heights(root->right_, 1);
    raise_heights(root->right_, 1);

    decrease_heights(root);
    raise_heights(new_root->right_->left_, 1);

    new_root->height_   += 2;

    root->right_height_ -= 2;
    new_root->right_->left_height_--;
    new_root-> left_height_ = root->left_height_ + 1;  // right height must not be higher than left
    new_root->right_height_ = new_root->right_->right_height_ + 1;
    
    if (new_root->right_->left_)
    {
        new_root->right_->left_height_ = 1 + max(new_root->right_->left_->left_height_, new_root->right_->left_->right_height_);
    }
    else
    {
        new_root->right_->left_height_ = 0;
    }

    new_root->position_ = root_pos;

    if (!recalc_positions(new_root))
        return NULL;

    return new_root;
}

node* right_small_turn(node* root)
{
    node* pre_root = NULL;
    bool root_is_right = false;
    if (root->parent_)
    {
        pre_root = root->parent_;
        root_is_right = root->is_right_;
    }


    int root_pos = root->position_;
    node* new_root = root->left_;
    new_root->parent_ = pre_root;
    new_root->is_right_ = root_is_right;

    if (root->left_->right_)
    {
        root->left_->right_->parent_ = root;
    }
    

    root->left_   = root->left_->right_;
    new_root->right_ = root;
    root->parent_ = new_root;

    decrease_heights(root->right_);
    root->height_--;

    raise_heights(new_root->left_, 1);
    new_root->height_++;

    printf("where sf \n");

    if (new_root->left_)    // probably both ifs are pointless
        new_root-> left_->is_right_ = false;
    if (new_root->right_)
        new_root->right_->is_right_ =  true;  

    printf("where sf \n");
    if (root->left_)
        root->left_->is_right_ = false; // not sure, just symmetry

    new_root->right_height_++;

    root->left_height_ = root->right_height_;

    
    new_root->position_ = root_pos;
    if (!recalc_positions(new_root))
        return NULL;

#if 0
/*
    printf("for 6: h = %d  l_h = %d, r_h = %d, pos = %d \n", root->height_, root->left_height_, root->right_height_, root->position_);
    printf("for 7: h = %d  l_h = %d, r_h = %d, pos = %d \n", new_root->height_, new_root->left_height_, new_root->right_height_, new_root->position_);
    printf("for 8: h = %d  l_h = %d, r_h = %d, pos = %d \n", new_root->right_->height_, new_root->right_->left_height_, new_root->right_->right_height_, new_root->right_->position_);
    */
#endif  // extra check

    return new_root;
}

node* right_big_turn(node* root)
{
    node* pre_root = NULL;
    bool root_is_right = false;
    
    int root_pos = root->position_;

    node* new_root = root->left_->right_;

    if (root->parent_)
    {
        pre_root = root->parent_;
        root_is_right = root->is_right_;
    }


    if (new_root->right_)
    {
        new_root->right_->parent_ = root; 
    }
    root->left_ = new_root->right_; 


    if (new_root->left_)
        new_root->left_->parent_ = new_root->parent_;

    new_root->parent_->right_ = new_root->left_;
    


    if (root->left_)
        root->left_->is_right_ = false;
   
    if (root->right_)
        root->right_->is_right_ = true;   



    if (new_root->parent_->right_)
        new_root->parent_->right_->is_right_ = true;
    

    if (new_root->parent_->left_)                    
    {
        new_root->parent_->left_->is_right_ = false;    
    }



    new_root->right_ = root;
    new_root->right_->parent_ = new_root;
    
    new_root->left_ = new_root->parent_;
    new_root->left_->parent_ = new_root;

    new_root->parent_ = pre_root;
    new_root->is_right_ = root_is_right;


    raise_heights(root->left_, 1);
    raise_heights(root->left_, 1); 
    decrease_heights(root);


    raise_heights(new_root->left_->right_, 1);

    new_root->height_   += 2;

    root->left_height_ -= 2;
    new_root->left_->right_height_--;
    new_root-> right_height_ = root->right_height_ + 1;  // right height must not be higher than left
    
    if (new_root->left_->right_)
    {
        new_root->left_->right_height_ = 1 + max(new_root->left_->right_->left_height_, new_root->left_->right_->right_height_);
    }
    else
    {
        new_root->left_->right_height_ = 0;
    }

    new_root->left_height_ = new_root->left_->left_height_ + 1;

    new_root->position_ = root_pos;

    new_root->right_->is_right_ = true;

#if 0
   /* printf("root->left = %d,root->right = %d,  root = %d \n", root->left_->value_, root->right_->value_, root->value_);                        

        if (!root->is_right_)
            printf("root is left \n");

        if (!root->left_->is_right_)
            printf("left is left \n");

        if (!root->right_->is_right_)
            printf("right is left \n");
*/
#endif  // extra check


    if (!recalc_positions(new_root))
        return NULL;

    return new_root;
}
int recalc_positions(node* root) // must not be problems wight parent, cause balancing leaves at least 2 levels
{
    if (!root)
        return 0;


    if (root->left_)
    {
        root->left_->position_ = root->position_ * 2;
        if (!recalc_positions(root->left_))
            return 0;
    }

    if (root->right_)
    {
        root->right_->position_ = root->position_ * 2 + 1;
        if (!recalc_positions(root->right_))
            return 0;
    }

    return 1;

}

///************************************
/// about queue
queue* add_elem(queue* end, node* leave)
{
    if (!end)        
        return NULL;

    if (!leave)
        return  end;


    queue* cur_obj = (queue*) malloc(sizeof(queue));
    if (!cur_obj)
    {
        printf("problems with memory allocation in add_elem funtion \n");
        return NULL;
    }


    cur_obj->next_  =  NULL;
    cur_obj->leave_ = leave;

    end->next_ = cur_obj;

    return cur_obj;
}


queue* dequeue(queue* front)
{
    if (!front)
        return front;       

    queue* new_front = front->next_;
    free(front);
    return new_front;
}


void q_print(queue* front)   // prints queue
{
    if (!front->next_)
        return;

    queue* cur_elem = front->next_;
    
    while (cur_elem)
    {
        printf("%d ", cur_elem->leave_->value_);
        cur_elem = cur_elem->next_;
    }
    printf("\n");
}
///***************************************


void smart_print(node* root, int max_ord)
{
    if (!root)
        return;

    queue* front = (queue*) calloc(1, sizeof(queue));
    queue*   end = (queue*) malloc(   sizeof(queue));
    if (!front || !end)
    {
        printf("problems with memory allocation in smart_print funtion \n");
        return;
    }
    end = front;

    bool if_h_0 = false;

    max_ord = max_ord + (1 - max_ord % 2);
    
    queue* cur_leave = add_elem(front, root);

    cur_leave = add_elem(cur_leave, root-> left_);
    cur_leave = add_elem(cur_leave, root->right_);

    int total_h = root->total_height_;
    int width    = to_degree(2, total_h) * (max_ord + 1) - 1; 
    int width_1d = to_degree(2, total_h + 1) - 1; 


 
    
    int d = (width_1d / to_degree(2, 1)) * ((max_ord + 1) / 2);
    int print_pos = d;

    print_space(d);
    
    print_n(root->value_, max_ord);
    print_space(d);
    printf("\n");

    front = dequeue(front);

    if (!front->next_)
        return;

    int  cur_pos   =           0;
    int line_pos   =           0;
    int kostyl_pos =           0;  // probably pointless
    int  cur_h     = total_h - 1;

#if 0
    //printf("d = %d, h = %d, cur_h = %d, cur_pos = %d \n", d, front->next_->leave_->height_, cur_h, cur_pos);
#endif  // extra check
    


    while (front->next_) 
    {
#if 0
        if (front->next_->leave_->height_ > cur_h)
        {
            decrease_heights(root);    
            dec_max_h(root);
            printf("all heights are decreased \n");
        }
#endif 

            

        if (front->next_->leave_->height_ < cur_h)
        {
            print_space(width - cur_pos);
            printf("\n");
            cur_pos = 0;
            cur_h--;


            if (cur_h < 0)  /// must not happen
            {
                //printf("height beda \n");
                return;
            }
        }

        cur_leave = add_elem(cur_leave, front->next_->leave_-> left_);
        cur_leave = add_elem(cur_leave, front->next_->leave_->right_);  ///  if NULL  returns cur_leave


        d = ((max_ord + 1) / 2) * (width_1d / to_degree(2, total_h - cur_h + 1)); // must not be calculated so often
        print_pos = d + front->next_->leave_->position_ * (2 * d + max_ord + 1);

        
        print_space(print_pos - cur_pos);

        print_n(front->next_->leave_->value_, max_ord);
#ifdef RLH
        printf("(%d %d)", front->next_->leave_->left_height_, front->next_->leave_->right_height_);
#endif   /// r/l heights control

#ifdef RL
        if (front->next_->leave_->is_right_)
        {
            printf("(r)");
        }
        else
        {
            printf("(l)");
        }
#endif // for right_left control

        kostyl_pos =   cur_pos + max_ord;
        cur_pos    = print_pos + max_ord;
        front = dequeue(front);

    }   
    free(front);
    print_space(width - cur_pos);
    printf("\n");
}



int to_degree(int value, int degree)
{
    int res = 1;

    for (int i = 0; i < degree; i++)
    {
        res *= value;
    }

    return res;

}

void print_space(int space_num)
{
    for (int i = 0; i < space_num; i++)
    {
        printf("-");
    }
}

void print_n(int value, int max_ord)
{


    int num = 0;
    int val = value;

    if (value == 0)
        num = 1;
    while (val)
    {
        val = val / 10;
        num++;
    }

    if (max_ord < num)
    {
        printf("given number is greater then it required. Trying to print using number of digits as max_ord \n");
        max_ord = num;  // probably here better return
    }

    for (int i = 0; i < max_ord - num; i++)
    {
        printf(GRN "_" RESET);
    }
    printf(GRN "%d" RESET, value);
}




/// iterators /*************************************


node* tree_begin(node* tree)
{
    return min_leave(tree);
}

node* inc(node* iter)
{
    node* cur_leave = iter;

//    printf("aaaaa \n");
    if (cur_leave->right_)
        return min_leave(iter->right_);

    
        // if no right

    bool cur_is_right = cur_leave->is_right_;

    if (!cur_leave->is_right_ && cur_leave->parent_)
    {
        return cur_leave->parent_;
    }

    do
    {
        if (!cur_leave->parent_)
            return NULL;
        cur_leave = cur_leave->parent_;
    }
    while (cur_leave->is_right_);

    
    if (cur_leave->parent_)
        return cur_leave->parent_;

    return NULL;

}




