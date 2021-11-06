/**
*********************************************************************************************************
*                                        		queue
*                                      (c) Copyright 2021-2031
*                                         All Rights Reserved
*
* @File    : 
* @By      : liwei
* @Version : V0.01
* 
*********************************************************************************************************
**/

/*
*********************************************************************************************************
Define
*********************************************************************************************************
*/
#define QUEUE_SIZE 	20
#define BUFF_SIZE 	3
/*
*********************************************************************************************************
Typedef
*********************************************************************************************************
*/
typedef struct key_data_def
{
	u8 buff[BUFF_SIZE];
}key_data_t;


typedef struct queue_key_def
{
	key_data_t  key_buff[QUEUE_SIZE];
	u8 front;
	u8 rear;
}queue_key_t;

/**
*********************************************************************************************************
* @名称	: queue_init
* @描述	:初始化队列
*********************************************************************************************************
**/
void queue_init(queue_key_t *queue)
{	
	queue->front = 1;
	queue->rear = 0;	
}
/**
*********************************************************************************************************
* @名称	: queue_full
* @描述	:检测队列是否为满
*********************************************************************************************************
**/
u8 queue_full(queue_key_t *queue)
{	
	return ( (queue->rear + 2)%QUEUE_SIZE == queue->front );
}
/**
*********************************************************************************************************
* @名称	: queue_empty
* @描述	:检测队列是否为空
*********************************************************************************************************
**/
u8 queue_empty(queue_key_t *queue)
{	
	return ( (queue->rear + 1)%QUEUE_SIZE == queue->front );
}
/**
*********************************************************************************************************
* @名称	: queue_delete
* @描述	:从列队头部删除一个数据
*********************************************************************************************************
**/
void queue_delete(queue_key_t *queue)
{
	
	if( !queue_empty(queue) )
	{
		/*清空数据*/
		memset( &queue->key_buff[ queue->front ] , 0 , sizeof( key_value_t ) );	
		queue->front = (queue->front + 1 )	% QUEUE_SIZE;
	}
}
/**
*********************************************************************************************************
* @名称	: queue_insert
* @描述	:从列队尾部插入一个数据
*********************************************************************************************************
**/
void queue_insert(queue_key_t *queue , key_value_t *data)
{
	
	if( !queue_full(queue) )
	{
		queue->rear = (queue->rear + 1 )	% QUEUE_SIZE;
		memcpy( &queue->key_buff[ queue->rear ] , data , sizeof( key_value_t ) );
	}
}
/**
*********************************************************************************************************
* @名称	: queue_read
* @描述	:读取队列头部数据
*********************************************************************************************************
**/
void queue_read(queue_key_t *queue , key_value_t *data)
{	
	if( !queue_empty(queue) )
	{
		/*复制数据*/
		memcpy( data , &queue->key_buff[ queue->front ] , sizeof( key_value_t ));
	}
}




/**
*********************************************************************************************************
* @名称	:
* @描述	:定义测试数据
*********************************************************************************************************
**/
key_value_t test_buff[10]=
{
	[1]=
	{
		.buff={11,22,33},
		.type = 1,
	},
	[8]=	
	{
		.buff={33,44,55},
		.type = 8,
	},	
};
key_value_t read_buff[10];


queue_key_t user_queue;
/**
*********************************************************************************************************
* @名称	:queue_test
* @描述	:测试程序
*********************************************************************************************************
**/
void queue_test(void)	
{
	/* 初始化队列user_queue */	
	queue_init(&user_queue);
	/*插入队列*/	
	for(u8 i  = 0 ; i < 10 ; i++)
	{
		queue_insert( &user_queue , &test_buff[i]);
	}
	/*读取队列数据，并删除队列数据*/		
	for(u8 i  = 0 ; i < 10 ; i++)
	{
		queue_read( &user_queue , &read_buff[i]);
		queue_delete( &user_queue);
	}
}
/***********************************************END*****************************************************/


