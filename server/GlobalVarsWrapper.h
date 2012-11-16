#pragma once

using namespace System;
using namespace SourceSDK::Core::Interfaces::Server;

extern CGlobalVars *gpGlobals;

ref class GlobalVarsWrapper : public NI_GlobalVars
{
public:
      virtual property String^ MapName
	  {
		  String^ get() sealed
		  {
			  return gcnew String(gpGlobals->mapname.ToCStr());
		  }
	  }

      virtual property String^ StartSpot
	  {
		  String^ get() sealed
		  {
			  return gcnew String(gpGlobals->startspot.ToCStr());
		  }
	  }

      virtual property int MapVersion
	  {
		  int get() sealed
		  {
			  return gpGlobals->mapversion;
		  }
	  }

      virtual property int MaxEntites
	  {
		  int get() sealed
		  {
			  return gpGlobals->maxEntities;
		  }
	  }

      virtual property int FrameCount
	  {
		  int get() sealed
		  {
			  return gpGlobals->framecount;
		  }
	  }

      virtual property int MaxClients
	  {
		  int get() sealed
		  {
			  return gpGlobals->maxClients;
		  }
	  }

      virtual property int TickCount
	  {
		  int get() sealed
		  {
			  return gpGlobals->tickcount;
		  }
	  }


      virtual property float RealTime
	  {
		  float get() sealed
		  {
			  return gpGlobals->realtime;
		  }
	  }

      virtual property float AbsFrameTime
	  {
		  float get() sealed
		  {
			  return gpGlobals->absoluteframetime;
		  }
	  }

      virtual property float CurTime
	  {
		  float get() sealed
		  {
			  return gpGlobals->curtime;
		  }
	  }

      virtual property float FrameTime
	  {
		  float get() sealed
		  {
			  return gpGlobals->frametime;
		  }
	  }

      virtual property float IntervalPerTick
	  {
		  float get() sealed
		  {
			  return gpGlobals->interval_per_tick;
		  }
	  }
};
