#include<window.h>
#include<graphics.h>
#include"Management.h"
#include"window.h"
#include"Table.h"
#include<iostream>


int main()
{
	windows w(640,480,2);
	w.setWindowTilte("GhostTyper");
	Management m;
	m.run();
	return w.exec();
 }
