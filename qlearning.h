////////////////////////////////////////////////////////////
///	INCLUDES
////////////////////////////////////////////////////////////
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

//Random number between 0 and 1
#define RANDF() (double)rand() / RAND_MAX 

typedef struct Qstruct
{
	float **table;
	int states_count;
	int actions_count;
	int state;
	int action;
	float learning_rate;
	float longterm_learning;
        float exploration_factor;
} Qstruct;

////////////////////////////////////////////////////////////
/// \brief	Create a Qstruct	
///
////////////////////////////////////////////////////////////
Qstruct* qstruct_init(int states_count, int actions_count)
{
	int i, k;
	Qstruct* q = (Qstruct*)malloc(sizeof(Qstruct));
	q->table = (float**)malloc(sizeof(float*) * states_count);
	for (i = 0; i < states_count; i++) {
		q->table[i] = (float*)malloc(sizeof(float) * actions_count);
		for (k = 0; k < actions_count; k++)
			q->table[i][k] = 0;
	}
	q->states_count = states_count;
	q->actions_count = actions_count;
	q->learning_rate = 0.5;
	q->longterm_learning = 0.5;
        q->exploration_factor = 0.1;
	return q;
}

////////////////////////////////////////////////////////////
/// \brief	Destroy a Qstruct	
///
////////////////////////////////////////////////////////////
void qstruct_free(Qstruct* q)
{
	int i;
	for (i = 0; i < q->states_count; i++)
		free(q->table[i]);
	free(q->table);
	free(q);
}

////////////////////////////////////////////////////////////
/// \brief	Return an action to perform based on the current
/// world state
///
////////////////////////////////////////////////////////////
int qstruct_takeaction(Qstruct* q, int state)
{
	//Exploration - Exploitation control 
	if (RANDF() < q->exploration_factor) {
                q->state = state;
		q->action = rand() % q->actions_count;
		return q->action;
	}

	//Get best action id and value
	double rmax = -0x7FFF;
	int maxid = 0;
	int i;
	for (i = 0; i < q->actions_count; i++)
		if (q->table[state][i] > rmax) {
			rmax = q->table[state][i];
			maxid = i;
		}

	//Select the best action as current action
	q->action = maxid;

	//Store current state for later
	q->state = state;

	return q->action;
}

////////////////////////////////////////////////////////////
/// \brief	Get maximum reward value at a particular state	
///
////////////////////////////////////////////////////////////
double qstruct_getmaxreward(Qstruct* q, int state)
{
	//Get max reward value at a particular state
	float rmax = -0x7FFF;
	int i;
	for (i = 0; i < q->actions_count; i++)
		if (q->table[state][i] > rmax) rmax = q->table[state][i];
	return rmax;
}

////////////////////////////////////////////////////////////
/// \brief	Update that Q matrix	
///
////////////////////////////////////////////////////////////
void qstruct_update(Qstruct* q, int state_new, float reward)
{
	//Update the Q matrix with based on world changes and reward feedbacks
	//This is the Qleaning rule
	q->table[q->state][q->action] += q->learning_rate * (reward +  
		q->longterm_learning * qstruct_getmaxreward(q, state_new) - q->table[q->state][q->action]);
}

#ifdef __cplusplus
}
#endif

