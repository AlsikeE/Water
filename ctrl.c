void ctrl_c(){
	Job *now = NULL;
    //前台没有作业直接返回
	if(fgPid == 0){
	    return;
	}
    //SIGNCHLD信号产生自此函数
	ingnore = 1;

	now = head;
	while (now != NULL && now -> pid != fgpid)
		now = now -> next;

	if (now == NULL){
		now = addJob(fgPid);    //没有前台作业则根据fgPid 添加
	}

	strcpy(now -> state, KILLED);
	now -> cmd[strlen(now -> cmd)] = '&';
	now -> cmd[strlen(now -> cmd) + 1] = '\0';
	printf("[%d]\t%s\t\t%s\n",now -> pid, now -> state, now -> cmd);

	kill (fgPid, SIGKILL);             //sigstop -> sigkill
	fgPid = 0;

	//需要删除在作业链表中的当前作业
	if (now == head ){
		head = now->next;
	}
	else
		last -> next =now ->next;
