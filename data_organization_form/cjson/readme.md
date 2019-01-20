- [sourceforge上的cjson](https://sourceforge.net/projects/cjson/)
- [github 上的 cjson](https://github.com/DaveGamble/cJSON)

- 本目录采用了 sourceforge上的cjson

## 有什么

```c

cjson官方代码
	cJSON.c cJSON.h test.c
各目录下的使用方法

```



### cjson 中的概念

- object

```c
类型 cJSON *
	cJSON_CreateObject

```

- item
```c
类型 cJSON *
	cJSON_CreateString cJSON_CreateArray  cJSON_CreateIntArray cJSON_CreateDoubleArray cJSON_CreateString 的返回值


```

- item 与 object 的创建


```c


/*
 *
 * 一个json结构体可以 是 数组,可以是下面的任一种,添加元素的时候,要根据不同 类别的规矩添加
 *

 cJSON *cJSON_CreateNull(void)					{cJSON *item=cJSON_New_Item();if(item)item->type=cJSON_NULL;return item;}
 cJSON *cJSON_CreateTrue(void)					{cJSON *item=cJSON_New_Item();if(item)item->type=cJSON_True;return item;}
 cJSON *cJSON_CreateFalse(void)					{cJSON *item=cJSON_New_Item();if(item)item->type=cJSON_False;return item;}
 cJSON *cJSON_CreateBool(int b)					{cJSON *item=cJSON_New_Item();if(item)item->type=b?cJSON_True:cJSON_False;return item;}
 cJSON *cJSON_CreateNumber(double num)			{cJSON *item=cJSON_New_Item();if(item){item->type=cJSON_Number;item->valuedouble=num;item->valueint=(int)num;}return item;}
 cJSON *cJSON_CreateString(const char *string)	{cJSON *item=cJSON_New_Item();if(item){item->type=cJSON_String;item->valuestring=cJSON_strdup(string);}return item;}
 cJSON *cJSON_CreateArray(void)					{cJSON *item=cJSON_New_Item();if(item)item->type=cJSON_Array;return item;}
 cJSON *cJSON_CreateObject(void)					{cJSON *item=cJSON_New_Item();if(item)item->type=cJSON_Object;return item;}

 Create Arrays:
 cJSON *cJSON_CreateIntArray(const int *numbers,int count)		{int i;cJSON *n=0,*p=0,*a=cJSON_CreateArray();for(i=0;a && i<count;i++){n=cJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
 cJSON *cJSON_CreateFloatArray(const float *numbers,int count)	{int i;cJSON *n=0,*p=0,*a=cJSON_CreateArray();for(i=0;a && i<count;i++){n=cJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
 cJSON *cJSON_CreateDoubleArray(const double *numbers,int count)	{int i;cJSON *n=0,*p=0,*a=cJSON_CreateArray();for(i=0;a && i<count;i++){n=cJSON_CreateNumber(numbers[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}
 cJSON *cJSON_CreateStringArray(const char **strings,int count)	{int i;cJSON *n=0,*p=0,*a=cJSON_CreateArray();for(i=0;a && i<count;i++){n=cJSON_CreateString(strings[i]);if(!i)a->child=n;else suffix_object(p,n);p=n;}return a;}

 * */
```

## 使用方法

```c
	一般都是 先 用上述 函数 创建一个 cJSON * item ,然后 cJSON_AddItemToObject 添加到root 或上层 object.
/*
 * 一般我们用 cJSON_CreateObject
 *                                  这下面可以挂 string int 任意类型json结构体 
 * 或者用 cJSON_CreateArray
 *                                  这里面第一个元素可以挂任何 东西,但是第二个元素必须要挂同等的东西
 *                                  在创建数组的时候并没有创建数组大小
 *
 * 或者用 cJSON_CreateStringArray
 *                                  这里面创建的时候已经 初始化完毕了.
 *
 * */

```
