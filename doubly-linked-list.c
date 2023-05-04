/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List 
 *
 * 자료구조 7번째 과제 
 * 충북대학교 2017015040 물리학과 강수
 */



#include<stdio.h>
#include<stdlib.h>


//구조체
typedef struct Node {
	int key;//키값
	struct Node* llink;//전링크
	struct Node* rlink;//후링크
} listNode;


//첫 번째 노드를 가르키는 구조체
typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

//초기화 함수
int initialize(headNode** h);//h의 값을 이중 포인터로 받아 바꾼다
int freeList(headNode* h);//메모리 값 해지 호출하는 곳의 값이 바뀌지 않는다

int insertNode(headNode* h, int key);//기존 값과 비교한 값보다 키값이 더 큰 위치에 저장
int insertLast(headNode* h, int key);//마지막에 저장
int insertFirst(headNode* h, int key);//처음에 저장

int deleteNode(headNode* h, int key);//해당 키값 삭제
int deleteLast(headNode* h);//마지막
int deleteFirst(headNode* h);//처음
int invertList(headNode* h);//역순으로 변경

void printList(headNode* h);//링크드 리스트 상태 출력


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;//해드노드를 가르키는 포인터
		printf("[-------------------- [kang su] [2017015040] -------------------]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);//이중 포인터 주소로 받는다
			break;
		case 'p': case 'P':
			printList(headnode);//
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


//초기화 함수
int initialize(headNode** h) {

    //기존 노드가 있을 경우 해당 노드를 초기화한다
	if(*h != NULL)
		freeList(*h);

	//시작 노드를 가르키는 주소할당
	*h = (headNode*)malloc(sizeof(headNode));//동적 할당된 주소값으로 시작 주소를 가르키는 주소를 변경
	(*h)->first = NULL;//첫 노드값이 NULL로 초기화

	return 1;
}


//전체 노드및 시작 노드를 가르키는 변수 해지 함수
int freeList(headNode* h){
    
    listNode* p = h->first;//초기노드 위치등록

	listNode* prev = NULL;//가르키는 노드의 이전노드
	while(p != NULL) {//노드가 값이 NULL일때 까지
		prev = p;//이전노드 등록
		p = p->rlink;//다음노드로 이동
		free(prev);//이전노드 해제
	}
	free(h);//초기 노드를 가르키는 변수 해지
	return 0;
}


//출력
void printList(headNode* h) {
	int i = 0;//노드번호
	listNode* p;//노드

	printf("\n---PRINT\n");

	if(h == NULL) {//출력할게 없는경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//처음노드

	while(p != NULL) {//처음부터 마지막 노드까지 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);
}



//마지막에 노드추가
int insertLast(headNode* h, int key) {


    listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 입력한 값을 저장한다
    node->rlink = NULL;//후 노드는 없으므로 NULL
	
    if(h->first==NULL){//등록된 노드가 없을경우
        node->llink =NULL;//전노드 없으므로 NULL
        h->first = node;//처음노드로 등록
        return 0;
    }

    //등록된 노드가 있는 경우

    listNode* n = h->first;//처음노드 부터시작
	while(n->rlink != NULL) {//마지막 노드까지 이동 n은 이미 등록되어 있는 마지막 노드가 된다
	    n = n->rlink;//다음 노드로 주소변경
	}

    //전노드 값 변경
	n->rlink = node;//이전 노드 이후 노드로 등록
	node->llink = n;//새로 등록된 노드 이전 노드 등록


	return 0;
}



//마지막 노드 제거
int deleteLast(headNode* h) {

	if (h->first == NULL)//지울 노드가 없는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//지울 노드가 있는경우
	listNode* n = h->first;//처음노드
	listNode* ln =NULL;//전 노드 초기화
	
	if(n->rlink==NULL){//n이 처음이고 n의 후 노드가 없는경우
		h->first = NULL;//초기 노드 없음 등록
		free(n);//n의 메모리 해지
		return 0;
	}

	//n의 전노드가 있는 경우
	while(n->rlink != NULL) {//마지막 노드 까지 이동
		ln= n;//전노드
	    n = n->rlink;//다음 노드로 주소변경
	}



	ln->rlink=NULL;//후 노드 없음 등록
	free(n);


	return 0;
}

//첫번째에 노드에 추가
int insertFirst(headNode* h, int key) {
    
    listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 입력한 값을 저장한다
    node->llink = NULL;//전 노드는 없으므로 NULL
	
	if(h->first == NULL)//후 노드가 없을경우
	{
        node->rlink =NULL;//후노드 없으므로 NULL
		h->first = node;//첫번째 노드로 등록
		return 0;
	}
    //후 노드가 있을 경우
    node->rlink = h->first;//전 첫번째 노드를 위치를 등록
	
    //후노드 값 변경
    listNode *p = h->first;//후 노드
	p->llink = node;//후 노드의 전노드를 새로 입력 한 노드로 등록
	h->first = node;//첫번째 노드로 새로 입력 받은 노드를 등록

	return 0;
}


//첫번째 노드 제거
int deleteFirst(headNode* h) {

	if (h->first == NULL)//지울 노드가 없는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	//지울 노드가 있는경우
	listNode* n = h->first;//처음노드

	h->first=n->rlink;//삭제한 노드의 후노드를 첫노드로 등록
	
	//후 노드가 없는 경우
	if(n->rlink==NULL){
		free(n);//n매모리 해지
		return 0;
	}
	//후노드가 있는 경우
	n->rlink->llink=NULL;//후노드의 전노드 없음 등록

	free(n);	
	return 0;


}


//노드 순서 역으로
int invertList(headNode* h) {
	
	if (h->first == NULL)//변환할 노드가 없는 경우
	{
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;//처음노드 등록
	listNode *bnode = NULL;//노드주소를 저장할 노드
	
	while (n->rlink!=NULL)//마지막 노드전까지 n은 마지막 노드에서 정지
	{
		bnode=n->rlink;//후노드값 등록
		n->rlink=n->llink;//후노드 값을 전노드로 변경
		n->llink=bnode;//전노드 값을 후노드값으로 변경
		n=bnode;//후노드로 이동
	}
	
	//마지막 노드에서
	bnode=n->rlink;//후노드값 등록
	n->rlink=n->llink;//후노드 값을 전노드로 변경
	n->llink=bnode;//전노드 값을 후노드값으로 변경
	h->first=n;//마지막 노드를 처음으로

	return 0;
}


//노드 추가
int insertNode(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));//노드생성
	node->key = key;//노드에 입력한 값을 저장한다
   
    if(h->first==NULL){//노드가 없을경우

        node->llink = NULL;//전 노드는 없으므로 NULL
        node->rlink = NULL;//후 노드는 없으므로 NULL
        h->first = node;//첫번째 노드로 등록
		return 0;// 종료
	}
	//이미 노드가 있을 경우

	listNode* n = h->first;//처음노드 부터시작 
	listNode* ln = NULL;//전 노드 초기화

	if((n->key<node->key)){//처음노드와 비교해서 클경우

        //새노드는 전노드와 후노드 사이에 들어간다 

		//전 노드가 있고 후 노드가 있을경우
		while(n != NULL&&(n->key<node->key)) {//비교해서 작지 않은 노드까지 이동 n은 크거나 같은 키값
			ln =n;//전 노드를 기억한다
			n = n->rlink;//다음 노드로 주소변경
		}

        //전노드에 등록
		ln->rlink=node;//전노드의 후노드로 새 노드등록
    
        if(n!=NULL)//후노드가 있는경우
    		n->llink=node;//후노드의 전노드로 새 노드 등록
    
        node->llink = ln;//전노드 등록
        node->rlink = n;//후노드 등록


			
	}else{//처음 노드 보다 작을경우, 전노드가 없고 후노드만 있는 경우
		node->llink = NULL;//전 노드는 없으므로 NULL
        node->rlink = n;//후 노드는 없으므로 NULL
	    n->llink = node;//후 노드의 전노드를 새로 입력 한 노드로 등록    
        h->first = node;//첫번째 노드로 등록
		return 0;//종료
	}

	return 0;
}


//노드제거
int deleteNode(headNode* h, int key) {

	if(h->first==NULL){//노드가 없을경우
		printf("nothing to delete.\n");
		return 0;// 종료
	}

	//지울 노드가 있는경우
	int worked=0;
	listNode* n = h->first;//첫번째 노드등록

	//후노드가 있는경우
	while(n->rlink != NULL) {//끝까지 반복
		//노드의 값이 일치한 경우
		if(n->key==key){
			if(n->llink==NULL){//해당 노드가 처음 노드인 경우	
				deleteFirst(h);
				worked++;
			}else{//해당 노드가 처음이 아니고 후노드가 있는 경우
				n->llink->rlink = n->rlink;//전노드의 후노드 값을 후노드 값으로 등록 
				n->rlink->llink = n->llink;//후노드의 전노드 값을 전노드 값으로 등록 
				free(n);//n메모리 해지
				worked++;
			}
		
			
		}
		n = n->rlink;//해당 노드or마지막 노드

	}
	//마지막 노드인경우	,후노드가 없는경우
	if(n->key==key){//노드 안에 해당 값이 있을 경우
		deleteLast(h);
		worked++;
		return 0;
	}
	if(!worked)
		printf("cannot find the node for key = %d\n", key);
	return 1;
}

