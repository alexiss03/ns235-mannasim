#include "leachAppModified.h"
#include <random.h>
#include <mannasim/battery.h>
#include <mannasim/leach/rca/rcagent.h>

/** TCL **************************************/

static class LeachAppWithResignationClass : public TclClass
{
        public:
                LeachAppWithResignationClass() : TclClass("Application/SensorBaseApp/CommonNodeApp/LeachAppWithResignation") {}

                // Create a TCL Object (parameters starts in 4)
                TclObject * create(int argc, const char * const * argv)
                {
			if (argc != 7)
			{
				fprintf(stderr,
					"Incorrect sintax:\n"
					"  new LeachAppWithResignation <nNodes> <nClusters> <maxDist>");
			}

                        return new LeachAppWithResignation(
                                atoi(argv[4]),
                                atoi(argv[5]),
				atof(argv[6]));
                }
} leach_app_object;




/*********************************************/

LeachAppWithResignation::LeachAppWithResignation(int nNodes, int nClusters, double maxDist) : CommonNodeApp() // : SensorBaseApp()
{
	mac_			 = NULL;
	agent_                   = NULL;

	isCH_                    = 0;
	hasBeenCH_               = false;
	nextChangeTime_          = 0;
	round_                   = 0;
	dist_                    = 0;
	code_                    = 0;
	now_                     = 0;
	endFrmTime_              = 0;
	beginIdle_               = 0;
	beginSleep_              = 0;
  initial_energy_          = 0;

	/* Although constructing here, can't determine
	 * sensedData's nodeid, because while constructing
	 * the sensed_node_ is not yet defined.
	 */
	sensedData_              = new SensedData();

	eventHandler_            = new LeachEventHandler(this);

	config_.numberNodes_     = nNodes;
	config_.desiredClusters_ = nClusters;
	config_.maxDist_         = bsDist_ = maxDist;

	initializeConfig();

	frameTime_               = config_.ssSlotTime_ * config_.numberNodes_ + 100;

	lstRndDelay_             = 0;

	listenADV_               = true;
	listenJOINREQ_           = false;
}

/* Initialize LEACH's configuration. */
void LeachAppWithResignation::initializeConfig()
{
	#define HDR_SIZE 25		// Originalmente era 25

	config_.changeTimeIncrement_ = 10 * config_.numberNodes_ ;
	config_.rndAdvDelay_         = TxTime(HDR_SIZE + 4);
	config_.ra_advTotal_         = 1 + config_.rndAdvDelay_ * (config_.desiredClusters_ * 4 + 1);
	config_.ra_join_             = 0.01 * config_.numberNodes_;
	config_.ra_delay_            = TxTime(HDR_SIZE + 4);
	config_.spreading_           = config_.desiredClusters_ + 1;
	config_.sigSize_             = 500;
	config_.ssSlotTime_          = TxTime(config_.sigSize_ + HDR_SIZE) * config_.spreading_;
	config_.bsCode_              = 0;

	#undef HDR_SIZE
}

LeachAppWithResignation::~LeachAppWithResignation()
{
	if (sensedData_ != NULL)
		delete sensedData_;

	delete eventHandler_;
}

void LeachAppWithResignation::start()
{
	if (agent_ == NULL)
	{
		char agentName[32];

		printf("Warning! LeachAppWithResignation::start() => agent_ of %d is null! Creating a RCAgent!\n", sensor_node_->nodeid());

		sprintf(agentName, "__rcagent%d", sensor_node_->nodeid());

		agent_ = new RCAgent();
		agent_->name(agentName);

		Tcl::instance().enter(agent_);

		printf("%s attach %s", name(), agent_->name());
		Tcl::instance().evalf("%s attach %s", name(), agent_->name());
	}

	sensedData_->node_id() == sensor_node_->nodeid();

	mac_ = (MacSensor *) ((RCAgent *) agent_)->getMAC();
	mac_->node_num() = sensor_node_->nodeid();
<<<<<<< HEAD

  decideClusterHead();

  initial_energy_ = ((Battery *) sensor_node_->energy_model())->energy();

	CommonNodeApp::start();

  printf("Initial energy of %d is  %f.\n", sensor_node_->nodeid(), initial_energy_);

=======
	decideClusterHead();

	CommonNodeApp::start();

  initial_energy_ = ((Battery *) sensor_node_->energy_model())->energy();
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::goToSleep()
{
	//((Battery *) sensor_node_->energy_model())->sleep();
}

void LeachAppWithResignation::wakeUp()
{
<<<<<<< HEAD
  ///((Battery *) sensor_node_->energy_model())->wakeUp();
=======
  //((Battery *) sensor_node_->energy_model())->wakeUp();
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::setCode(int code)
{
	//printf("%d is setting code to %d\n", sensor_node_->nodeid(), code);
<<<<<<< HEAD
//  code_        = 0;
//  mac_->code() = 0;
  code_        = code;
  mac_->code() = code;
=======
  code_        = 0;
  mac_->code() = 0;
  //code_        = code;
  //mac_->code() = code;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::setClusterHead()
{
	isCH_      = true;
	hasBeenCH_ = true;
	/* "... when a node decides to become a cluster-head,
	 * it chooses randomly from a list of spreading codes."
	 */
}

void LeachAppWithResignation::unsetClusterHead()
{
	isCH_      = false;
}

/*** Distributed cluster set-up functions *****************/

void LeachAppWithResignation::decideClusterHead()
{
<<<<<<< HEAD
  double energy_ = ((Battery *) sensor_node_->energy_model())->energy();

  //printf("Decide cluster head of %d at time %lf round: %d at energy level %d\n", sensor_node_->nodeid(), Scheduler::instance().clock(), round_, energy_);
=======
  printf("Decide cluster head of %d at time %lf round: %d\n", sensor_node_->nodeid(), Scheduler::instance().clock(), round_);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	int totRounds;

	setCode(0);
	wakeUp();

	CHHeard_  = false;
<<<<<<< HEAD
  // Mary Alexis Solis
=======
  // Mayr Alexis Solis
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
  isCH_ = false;
  //hasBeenCH_ = false;

	// CheckIsAlive???

	totRounds = config_.numberNodes_ / config_.desiredClusters_;
  //printf("Total rounds: %d", totRounds);

<<<<<<< HEAD
	if (round_ >= totRounds) {
//  if (round_ >= 1) {
=======
	//if (round_ >= totRounds) {
  if (round_ >= 3) {
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
		round_ = 0;
  }

	if (round_ == 0) {
		setHasNotBeenClusterHead();
<<<<<<< HEAD
    //isCH_ = false;
=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
  }

	if (Random::uniform(0, 1) < calculatePi())
	{
<<<<<<< HEAD
		printf("Node %d is a cluster head at time %lf with energy: %f\n", sensor_node_->nodeid(), Scheduler::instance().clock(), energy_);
=======
		printf("Node %d is a cluster head at time %lf\n", sensor_node_->nodeid(), Scheduler::instance().clock());
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

		setClusterHead();

		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::advertiseClusterHead),
<<<<<<< HEAD
     //Scheduler::instance().clock() + 0.01);
    //  config_.rndAdvDelay_);
    0.01);

    //advertiseClusterHead();
	}
	else
	{

    printf("Node %d is a common node at time %lf with energy: %f\n", sensor_node_->nodeid(), Scheduler::instance().clock(), energy_);
		unsetClusterHead();
		listenADV_ = true;
		//clearClusterChoices();
	}

	round_++;
	//nextChangeTime_ = Scheduler::instance().clock() + config_.changeTimeIncrement_;
  nextChangeTime_ = config_.changeTimeIncrement_;
=======
      Scheduler::instance().clock());
      //config_.rndAdvDelay_);
	}
	else
	{
		unsetClusterHead();
		listenADV_ = true;
		clearClusterChoices();
	}

	round_++;
	nextChangeTime_ = Scheduler::instance().clock() + config_.changeTimeIncrement_;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

	Scheduler::instance().schedule(
		eventHandler_,
		new LeachEvent(&LeachAppWithResignation::decideClusterHead),
<<<<<<< HEAD
  	nextChangeTime_);
	//  config_.changeTimeIncrement_);
=======
  	 //nextChangeTime_);
	  config_.changeTimeIncrement_);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

	Scheduler::instance().schedule(
		eventHandler_,
		new LeachEvent(&LeachAppWithResignation::findBestCluster),
<<<<<<< HEAD
   Scheduler::instance().clock() + config_.ra_advTotal_);
  //  Scheduler::instance().clock() + config_.ra_advTotal_+20);
=======
    Scheduler::instance().clock() + config_.ra_advTotal_ + 20);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
    //+config_.rndAdvDelay_);
    //config_.ra_advTotal_);
}

double LeachAppWithResignation::calculatePi()
{
	/*
	 * Pi(t) = k / (N - k mod(r,N/k))
	 * where k is the expected number of clusters per round
	 * N is the total number of sensor nodes in the network
	 * and r is the number of rounds that have already passed.
	 */
	register int n = config_.numberNodes_;
	register int k = config_.desiredClusters_;
	double thresh;

	if (hasBeenClusterHead())
		thresh = 0;
  //else
<<<<<<< HEAD
  else if (n - k * round_ < 1)
//  else if (round_ == 1)
		thresh = 1;
 else
// thresh = 1;
  //thresh = (double) k / n * 3;
=======
	//else if (n - k * round_ < 1)
  else if (round_ == 1)
		thresh = 1;
 else
  //thresh = 1;
//  thresh = (double) k / n * 3;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	thresh = (double) k / (n - k * round_);

  //printf("Threshold %f\n",thresh);

//  return 1.0;
	return thresh;
}

void LeachAppWithResignation::advertiseClusterHead()
{
	int clusterCode;
	int numCodesAvail;

	numCodesAvail = 2 * config_.spreading_ - 1;


	currentCH_ = sensor_node_->nodeid();
	currentCHMAC_ = MAC_BROADCAST;

	clusterCode = (mac_->myADVnum() % numCodesAvail) + 1;

<<<<<<< HEAD
	//setCode(clusterCode);

	wakeUp();

  double energy_ = ((Battery *) sensor_node_->energy_model())->energy();
  printf("SENDING ADV_CH from %d at %lf link broadcast: %d at energy: %d\n", currentCH_, Scheduler::instance().clock(), LINK_BROADCAST, energy_);
=======
	setCode(clusterCode);

	wakeUp();
  printf("Adverstise cluster head \n");
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

	send(
		MAC_BROADCAST,
		LINK_BROADCAST,
		LEACH_ADV_CH,
		(char *) (&code_),
		sizeof(currentCH_),
		BYTES_ID,
		config_.maxDist_,
		0);

	listenJOINREQ_ = true;
	clusterNodes_.clear();
}

void LeachAppWithResignation::findBestCluster()
{
<<<<<<< HEAD
  printf("Started to find best cluster for %d at time:%lf isClusterHead: %d\n", sensor_node_->nodeid(), Scheduler::instance().clock(), isClusterHead());
=======
  printf("Started to find best cluster at time:%lf\n", Scheduler::instance().clock());
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
//	int numCodesAvail, clusterCode;

//	numCodesAvail = 2 * config_.spreading_ - 1;

	if (isClusterHead())
	{
		// If node is CH, determine code and create a TDMA schedule.
		dist_      = config_.maxDist_;
		currentCH_ = sensor_node_->nodeid();
		currentCHMAC_ = MAC_BROADCAST;
//		myADVnum_  = mac_->myADVnum();

		/* There are opt(spreading) - 1 codes available b/c need 1 code
		 * for communication with the base station.
		 */
//		clusterCode   = (myADVnum_ % numCodesAvail) + 1;

		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::createSchedule),
<<<<<<< HEAD
      0.01);
    //  Scheduler::instance().clock()+config_.ra_advTotal_);
    //  config_.ra_advTotal_ + config_.ra_join_);
=======
      Scheduler::instance().clock()+config_.ra_advTotal_);
      //config_.ra_advTotal_ + config_.ra_join_);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	}
	else
	{
		int clusterCode;

		/* If node is not a CH, find the CH which allows minimum transmit
		 * power for communication.  Set the code and "distance" parameters
		 * accordingly.
		 */
		if (clusterChoices_.empty())
		{
			printf("Warning! No Cluster Head ADVs were heard by %d\n", sensor_node_->nodeid());
			currentCH_ = -1;	// VER ISSO *****
			currentCHMAC_ = MAC_BROADCAST;
			sendMyDataToBS();
			return;
		}

		double min_dist = config_.maxDist_ + 1;
		int ind = 0;

		for (CHs::iterator it = clusterChoices_.begin(); it != clusterChoices_.end(); it++, ind++)
		{
			chadv element = (chadv) *it;

			if (element.distance < min_dist)
			{
				min_dist    = element.distance;
				currentCH_  = element.nodeid;
				currentCHMAC_ = element.mac;
//				clusterCode = (ind % numCodesAvail) + 1;
				clusterCode = element.code;
			}
		}

		dist_ = min_dist;

		printf("%d has choosen %d as cluster head (mac = %d)\n", sensor_node_->nodeid(), currentCH_, currentCHMAC_);

		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::informClusterHead),
<<<<<<< HEAD
      0.01);
     //Scheduler::instance().clock() +  Random::uniform(0, config_.ra_join_ - config_.ra_delay_));
      //+config_.ra_advTotal_ + Random::uniform(0, config_.ra_join_ - config_.ra_delay_));
		  //config_.ra_advTotal_ + Random::uniform(0, config_.ra_join_ - config_.ra_delay_));;

    //  informClusterHead();

		//goToSleep();
		//setCode(clusterCode);
    setCode(0);
=======
      Scheduler::instance().clock());
      //+config_.ra_advTotal_ + Random::uniform(0, config_.ra_join_ - config_.ra_delay_));
		 //config_.ra_advTotal_ + Random::uniform(0, config_.ra_join_ - config_.ra_delay_));;

		goToSleep();


		setCode(clusterCode);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

		printf("Current cluster-head of %d is %d, which code is %d, at distance is %lf\n",
			sensor_node_->nodeid(),
			currentCH_,
			clusterCode,
			dist_);
	}

<<<<<<< HEAD
	//listenADV_ = false;
	clearClusterChoices();
}

// void LeachAppWithResignation::informClusterHead()
// {
// 	int dataSize;
// 	int nodeId;
//
// 	printf("%d sending JOIN_REQ to %d, distance = %lf , at time %lf\n",
// 		sensor_node_->nodeid(),
// 		currentCH_,
// 		dist_,
// 		Scheduler::instance().clock());
//
// 	dataSize = config_.spreading_ * BYTES_ID;
// 	nodeId   = sensor_node_->nodeid();
//
//   //listenADV_ = true;
//
// 	send(
// 		currentCHMAC_,
// 		currentCH_,
// 		LEACH_JOIN_REQ,
// 		(char *) (&nodeId),
// 		sizeof(int),
// 		dataSize,
// 		config_.maxDist_ + 1,		// Using maxDist_, the CH can discover node's distance
// 		code_);
// }



=======
	listenADV_ = false;
	clearClusterChoices();
}

>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
void LeachAppWithResignation::informClusterHead()
{
	int dataSize;
	int nodeId;

	printf("%d sending JOIN_REQ to %d, distance = %lf , at time %lf\n",
		sensor_node_->nodeid(),
		currentCH_,
		dist_,
		Scheduler::instance().clock());

	dataSize = config_.spreading_ * BYTES_ID;
	nodeId   = sensor_node_->nodeid();

<<<<<<< HEAD
	send(
//		MAC_BROADCAST,
=======
  listenADV_ = true;

	send(
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
		currentCHMAC_,
		currentCH_,
		LEACH_JOIN_REQ,
		(char *) (&nodeId),
		sizeof(int),
		dataSize,
<<<<<<< HEAD
		config_.maxDist_,		// Using maxDist_, the CH can discover node's distance
//		dist_,
		code_);
}



// Modified by Mary Alexis Solis
void LeachAppWithResignation::challengeNodeAsNewClusterHead()
=======
		config_.maxDist_ + 1,		// Using maxDist_, the CH can discover node's distance
		code_);
}

// Modified by Mary Alexis Solis
void LeachAppWithResignation::challegeNodeAsNewClusterHead()
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
{
  int dataSize;

  for (CNs::iterator it = clusterNodes_.begin(); it != clusterNodes_.end(); it++)
  {
    dataSize = config_.spreading_ * BYTES_ID;
    printf("Sending LEACH_CHALLENGE_NODE from %d to sensor node %d\n", *it, currentCH_);

  	send(
  		MAC_BROADCAST,
  		*it,
  		LEACH_CHALLENGE_NODE,
  		(char *) (&currentCH_),
      sizeof(int),
  		dataSize,
  		config_.maxDist_,		// Using maxDist_, the CH can discover node's distance
  		code_);

    break;
  }

}

// Modified by Mary Alexis Solis
void LeachAppWithResignation::acceptChallengeAsClusterHead(int src)
{
  int dataSize;
  int nodeId;

<<<<<<< HEAD
  setClusterHead();

=======
  isCH_   = true;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
  dataSize = config_.spreading_ * BYTES_ID;
  nodeId = sensor_node_->nodeid();

  printf("Sending LEACH_ACCEPT_CHALLENGE\n");
  //
	send(
		currentCHMAC_,
		src,
		LEACH_ACCEPT_CHALLENGE,
		(char *) (&nodeId),
		sizeof(int),
		dataSize,
		config_.maxDist_,	// using maxDist_, the CH can discover node's distance
		code_);
}

void LeachAppWithResignation::resignClusterHead(int src)
{
	int dataSize;
	int nodeId;

  isCH_      = false;
  hasBeenCH_ = true;

<<<<<<< HEAD
	printf("Sending resignation to member nodes.\n");
=======
	printf("Sending resignation to member nodes");
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

	dataSize = config_.spreading_ * BYTES_ID;
	nodeId   = sensor_node_->nodeid();

<<<<<<< HEAD
  // for (CNs::iterator it = clusterNodes_.begin(); it != clusterNodes_.end(); it++)
  // {
  //   dataSize = config_.spreading_ * BYTES_ID;
  //   printf("Sending resignation %d sensor node %d\n\n\n", *it, currentCH_);
  //
  //   send(
  //     MAC_BROADCAST,
  //     LINK_BROADCAST,
  //     LEACH_RESIGN_CH,
  //     (char *) (&currentCH_),
  //     sizeof(int),
  //     dataSize,
  //     config_.maxDist_,		// Using maxDist_, the CH can discover node's distance
  //     code_);
  // }

  send(
    MAC_BROADCAST,
    LINK_BROADCAST,
    LEACH_RESIGN_CH,
    (char *) (&currentCH_),
    sizeof(int),
    dataSize,
    config_.maxDist_,		// Using maxDist_, the CH can discover node's distance
    code_);
=======
  for (CNs::iterator it = clusterNodes_.begin(); it != clusterNodes_.end(); it++)
  {
    dataSize = config_.spreading_ * BYTES_ID;
    printf("Sending resignation %d sensor node %d\n\n\n", *it, currentCH_);

  	send(
  		MAC_BROADCAST,
  		*it,
  		LEACH_RESIGN_CH,
  		(char *) (&src),
      sizeof(int),
  		dataSize,
  		config_.maxDist_,		// Using maxDist_, the CH can discover node's distance
  		code_);
  }
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}


void LeachAppWithResignation::createSchedule()
{
<<<<<<< HEAD
  //return;
	if (clusterNodes_.empty())
	{
		printf("Warning! There are no nodes in cluster %d\n",
			sensor_node_->nodeid());
=======
	if (clusterNodes_.empty())
	{
		//printf("Warning! There are no nodes in cluster %d\n",
		//	sensor_node_->nodeid());
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
		sendMyDataToBS();
	}
	else
	{
		int * msg;
		int i = 0;
		int dataSize;

		msg = new int[clusterNodes_.size()];

		printf("%d sending TDMA schedule (ADV_SCH): ", sensor_node_->nodeid());

		for (CNs::iterator it = clusterNodes_.begin(); it != clusterNodes_.end(); it++)
		{
			msg[i++] = (int) *it;
			printf("%d ", (int) *it);
		}

		printf("at time %lf\n", Scheduler::instance().clock());
<<<<<<< HEAD
		dataSize = config_.spreading_ * sizeof(int) * clusterNodes_.size();
=======

		dataSize = config_.spreading_ * sizeof(int) * clusterNodes_.size();

>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
		tdmaSchedule_.assign(clusterNodes_.begin(), clusterNodes_.end());

		send(
			MAC_BROADCAST,
			LINK_BROADCAST,
			LEACH_ADV_SCH,
			(char *) msg,
			sizeof(int) * clusterNodes_.size(),
			dataSize,
			dist_,
			code_);

<<<<<<< HEAD
		//listenJOINREQ_ = false;
=======
		listenJOINREQ_ = false;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495


		frameTime_   = (5 + clusterNodes_.size()) * config_.ssSlotTime_;
		lstRndDelay_ = Random::uniform(0, 0.01);
		xmitTime_    = config_.ssSlotTime_ * (clusterNodes_.size()) + lstRndDelay_;

		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::sendDataToBS),
<<<<<<< HEAD
      //Scheduler::instance().clock() +xmitTime_);
      xmitTime_);
	 }
=======
      Scheduler::instance().clock() +xmitTime_);
      //xmitTime_);
	}
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

/*********************************************************/

void LeachAppWithResignation::recv(int type, double distance, int link_dst, int size, char * meta, int meta_size, int src_mac, int src_lnk)
{
<<<<<<< HEAD
=======
  double energy_ = ((Battery *) sensor_node_->energy_model())->energy();
  //printf("Current energy: %f out of %f.\n", energy_, initial_energy_);

  if (initial_energy_ == 0) {
    initial_energy_ = energy_;
  }

  if (isClusterHead()  && energy_ < initial_energy_ * 0.99) {
    initial_energy_ = energy_;

    Scheduler::instance().schedule(
      eventHandler_,
      new LeachEvent(&LeachAppWithResignation::challegeNodeAsNewClusterHead),
      Scheduler::instance().clock());
    //  return;
  }
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
//  printf("Receiving... %d\n", type);

  #ifdef CHATO
  	printf("Receiving packet at %lf => ", Scheduler::instance().clock());
  #endif

  //	if (link_dst < 0) // || link_dst == sensor_node_->nodeid())
  		switch (type)
  		{
        case LEACH_CHALLENGE_NODE:
        #ifdef CHATO
          printf("LEACH_CHALLENGE_NODE\n");
        #endif
          recvChallengeNode(meta, meta_size, distance, src_mac, src_lnk);
          break;

        case LEACH_ACCEPT_CHALLENGE:
          #ifdef CHATO
            printf("LEACH_ACCEPT_CHALLENGE\n");
          #endif
            recvAcceptChallengeNode(meta, meta_size, distance, src_mac, src_lnk);
          break;

        case LEACH_RESIGN_CH:
          #ifdef CHATO
            printf("LEACH_RESIGN_CH\n");
          #endif
            recvClusterHeadResignNode(meta, meta_size, distance, src_mac, src_lnk);
          break;

  			case LEACH_ADV_CH:
          #ifdef CHATO
          				printf("LEACH_ADV_CH\n");
          #endif
  //				if (isClusterHead())
  				recvADV_CH(meta, meta_size, distance, src_mac, src_lnk);
  				break;

  			case LEACH_JOIN_REQ:
          #ifdef CHATO
          				printf("JOIN_REQ\n");
          #endif
  //				if (sensor_node_->nodeid() == link_dst)
  					recvJOIN_REQ(meta, meta_size);
  				break;

  			case LEACH_ADV_SCH:
          #ifdef CHATO
          				printf("LEACH_ADV_SCH\n");
          #endif
  				recvADV_SCH(meta, meta_size, src_mac);
  				break;

  			case LEACH_DATA:
          #ifdef CHATO
          				printf("LEACH_DATA\n");
          #endif
  //				if (sensor_node_->nodeid() == link_dst)
  					recvData(meta, meta_size);
  				break;

  			case LEACH_BS_HELLO:
          #ifdef CHATO
          				printf("LEACH_BS_HELLO\n");
          #endif
  				recvBSHello(meta, meta_size, distance);
  				break;

  			default:
          break;
  			  //printf(stderr, "Unknown received data type on LeachAp %d!\n", type);
  				//exit(-1);
  		}
<<<<<<< HEAD

=======
  //	else
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
  //		fprintf(stderr, "Received a packet addressed to another node!\n");
}

void LeachAppWithResignation::recvChallengeNode(char * msg, int size, double distance, int src, int lnk_src)
{

		printf("%d received LEACH_CHALLENGE_NODE from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
			sensor_node_->nodeid(),
			lnk_src,
			src,
			distance,
			*((int *) msg),
			Scheduler::instance().clock());

<<<<<<< HEAD
      acceptChallengeAsClusterHead(*((int *) msg));
=======
      acceptChallengeAsClusterHead(src);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::recvAcceptChallengeNode(char * msg, int size, double distance, int src, int lnk_src)
{

		printf("%d received LEACH_ACCEPT_CHALLENGE from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
			sensor_node_->nodeid(),
			lnk_src,
			src,
			distance,
			*((int *) msg),
			Scheduler::instance().clock());

    resignClusterHead(src);
}

void LeachAppWithResignation::recvClusterHeadResignNode(char * msg, int size, double distance, int src, int lnk_src)
{
<<<<<<< HEAD
  if (!isClusterHead() && currentCH_ == lnk_src) {
=======
  if (!isClusterHead()) {
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
    currentCH_ = *(int *) msg;

    printf("%d received LEACH_RESIGN_CH from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
      sensor_node_->nodeid(),
      lnk_src,
      src,
      distance,
      *((int *) msg),
      Scheduler::instance().clock());
<<<<<<< HEAD
  } else if(!isClusterHead()) {
    // printf("%d received LEACH_RESIGN_CH but is NOT  a previous member from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
    //   sensor_node_->nodeid(),
    //   lnk_src,
    //   src,
    //   distance,
    //   *((int *) msg),
    //   Scheduler::instance().clock());
=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
  }
}

void LeachAppWithResignation::recvADV_CH(char * msg, int size, double distance, int src, int lnk_src)
{
	if (listenADV_)
	{
		chadv element;

<<<<<<< HEAD
		if (!isClusterHead()) {
=======
		if (!isClusterHead())
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
			printf("%d received ADV_CH from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
				sensor_node_->nodeid(),
				lnk_src,
				src,
				distance,
				*((int *) msg),
				Scheduler::instance().clock());
<<<<<<< HEAD
    } else {
      printf("%d received ADV_CH but is CLUSTER HEAD from %d (mac = %d, distance = %lf, code = %d) at %lf\n",
				sensor_node_->nodeid(),
				lnk_src,
				src,
				distance,
				*((int *) msg),
				Scheduler::instance().clock());
    }
=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495

		element.nodeid   = lnk_src;
		element.distance = distance;
		element.mac      = src;
		element.code     = *((int *) msg);
		element.object   = NULL;

		clusterChoices_.push_back(element);
	} else {
    printf("Node is not listening to ADV_CH ");
  }
}


void LeachAppWithResignation::recvJOIN_REQ(char * msg, int size)
{
	if (!isClusterHead())
	{
		fprintf(stderr, "Node %d received a JOIN_REQ from %d but it's not a cluster head!\n",
			sensor_node_->nodeid(),
			*((int *) msg));
      return;
		//exit(-1);
	}

	if (listenJOINREQ_)
	{
<<<<<<< HEAD
    double energy_ = ((Battery *) sensor_node_->energy_model())->energy();
		printf("%d received JOIN_REQ from %d at %lf with energy: %f initial energy %f \n",
			sensor_node_->nodeid(),
			*((int *) msg),
			Scheduler::instance().clock(),
      energy_,
      initial_energy_);

		clusterNodes_.push_back(*((int *) msg));

    //Scheduler::instance().schedule(
    //  eventHandler_,
    //  new LeachEvent(&LeachAppWithResignation::challengeNodeAsNewClusterHead),
    //  xmitTime_);


    if (energy_ < initial_energy_ * 0.99) {
      printf("Start resignation.\n");
      initial_energy_ = energy_;
      //exit(-1);
    //if (isClusterHead()) {


      Scheduler::instance().schedule(
       eventHandler_,
       new LeachEvent(&LeachAppWithResignation::challengeNodeAsNewClusterHead),
       0.01);


      // Scheduler::instance().clock());
      //challegeNodeAsNewClusterHead();
      //  return;
    }
=======
		printf("%d received JOIN_REQ from %d at %lf\n",
			sensor_node_->nodeid(),
			*((int *) msg),
			Scheduler::instance().clock());

		clusterNodes_.push_back(*((int *) msg));

    // Scheduler::instance().schedule(
    //   eventHandler_,
    //   new LeachEvent(&LeachAppWithResignation::challegeNodeAsNewClusterHead),
    //   xmitTime_);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	}
	else
		printf("%d received a late JOIN_REQ from %d at %lf\n",
			sensor_node_->nodeid(),
			*((int *) msg),
			Scheduler::instance().clock());
}

void LeachAppWithResignation::recvADV_SCH(char * msg, int size, int src)
{
	int * vector = (int *) msg;
	int elements = size / sizeof(int);
	int nodeid   = sensor_node_->nodeid();
	double xmitat;

	if (src == currentCHMAC_)
	{
		printf("%d received ADV_SCH from %d at %lf\n",
			sensor_node_->nodeid(),
			src,
			Scheduler::instance().clock());

		for (int i = 0; i < elements; i++)
			if (vector[i] == nodeid)
			{
				/* Determine time for a single TDMA frame. Each node sends data once
				 * per frame in the specified slot.
				 */
				frameTime_  = (5 + elements) * config_.ssSlotTime_;
				xmitTime_   = config_.ssSlotTime_ * i;
				endFrmTime_ = frameTime_ - xmitTime_;
				xmitat      = Scheduler::instance().clock() + xmitTime_;

				printf("Node %d schedule to transmit at %lf (%lf) | It is now %lf\n",
					nodeid,
					xmitat,
					xmitTime_,
					Scheduler::instance().clock());

				if (xmitat + endFrmTime_ < nextChangeTime_ - 10 * config_.ssSlotTime_)
				{
					Scheduler::instance().schedule(
						eventHandler_,
						new LeachEvent(&LeachAppWithResignation::sendData),
<<<<<<< HEAD
          //  Scheduler::instance().clock()+xmitTime_);
            xmitTime_);
            return;
					//goToSleep();
				}
				//else
				//	printf("teste!!!!!!!\n");

=======
            Scheduler::instance().clock()+xmitTime_);
            //xmitTime_);

					goToSleep();
				}
				else
					printf("teste!!!!!!!\n");
				return;
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
			}

		// There is no time slot available
		printf("Warning!!! %d doesn't have a transmit time for CH %d!\n", sensor_node_->nodeid(), currentCH_);

		sendMyDataToBS();
	}
}

void LeachAppWithResignation::recvData(char * msg, int size)
{

	printf("CH %d received data from %d at %lf",
		sensor_node_->nodeid(),
		((SensedData *) msg)->node_id(),
		Scheduler::instance().clock());

	mergeSensedData((SensedData *) msg);

	printf(" - Now there is %d sensed data\n",
		sensedData_->getData().size());
}

/* Occurs when received a base station "hello".
 * This is usefull to determine the BS distance from
 * node, but it is not original from LEACH paper.
 * -- J�lio C�sar e Melo
 */
void LeachAppWithResignation::recvBSHello(char * msg, int size, double distance)
{
	bsDist_ = distance;

	printf("Node %d received BS_Hello at distance %lf\n",
		sensor_node_->nodeid(),
		distance);
}

/*********************************************************/

void LeachAppWithResignation::sendData()
{
<<<<<<< HEAD
  return;
=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	int    dataSize;
	double xmitat;

	if (sensedData_->count() > 0 && !isClusterHead())
	{
		dataSize = config_.spreading_ * (BYTES_ID * sensedData_->msgSize() + config_.sigSize_);

		wakeUp();

		printf("Node %d sending %d data to CH %d at %lf | d = %lf\n",
			sensor_node_->nodeid(),
			sensedData_->count(),
			currentCH_,
			Scheduler::instance().clock() + frameTime_,
			dist_);

		sensedData_->node_id() = sensor_node_->nodeid();

		send(
	//		MAC_BROADCAST,
			currentCHMAC_,
			currentCH_,
			LEACH_DATA,
			sensedData_,
			dataSize,
			dist_,
			code_);

		// sensedData_ = new SensedData();
		clearSensedData();

<<<<<<< HEAD
	//	if (!isClusterHead())
			//goToSleep();
=======
		if (!isClusterHead())
			goToSleep();
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	}

	xmitat = Scheduler::instance().clock() + frameTime_;

	if (xmitat + endFrmTime_ < nextChangeTime_ - 10 * config_.ssSlotTime_)
		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::sendData),
<<<<<<< HEAD
      //Scheduler::instance().clock()+frameTime_);
      frameTime_);
=======
      Scheduler::instance().clock()+frameTime_);
      //frameTime_);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::send(int mac_dst, int link_dst, int type, char * msg, int msg_size, int data_size, double dist, int code)
{
	if (dist <= 0)
	{
		printf("Distancia invalida! %lf\n", dist);
		//exit(-1);
    return;
	}

	((RCAgent *) agent_)->sendmsg(
		data_size,
		msg,
		msg_size,
		mac_dst,
		link_dst,
		dist,
		code,
		type);
}

void LeachAppWithResignation::send(int mac_dst, int link_dst, int type, void * msg, int msg_size, int data_size, double dist, int code)
{
	send(
		mac_dst,
		link_dst,
		type,
		(char *) msg,
		msg_size,
		data_size,
		dist,
		code);
}

void LeachAppWithResignation::send(int mac_dst, int link_dst, int type, SensedData * msg, int data_size, double dist, int code)
{
	send(
		mac_dst,
		link_dst,
		type,
		(char *) msg,
		msg->msgSize(),
		data_size,
		dist,
		code);
}

void LeachAppWithResignation::sendDataToBS()
{
<<<<<<< HEAD
  //return;
=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	int    dataSize, compressedSize;
	double dist;
	double xmitat;
	double rndDelay;

	rndDelay     = Random::uniform(0, 0.01);
	xmitat       = rndDelay - lstRndDelay_ + frameTime_;
	lstRndDelay_ = rndDelay;

<<<<<<< HEAD
	if (sensedData_->count() > 100)
=======
	if (sensedData_->count() > 0)
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	{
		dataSize = config_.spreading_ * (BYTES_ID * sensedData_->msgSize() + config_.sigSize_);

		if (!isClusterHead())
			wakeUp();

		//printf("Node %d sending %d data to BS at time %lf\n",
		//	sensor_node_->nodeid(),
		//	sensedData_->count(),
		//	Scheduler::instance().clock());

		sensedData_->timeStamp() = Scheduler::instance().clock();
		sensedData_->node_id() = sensor_node_->nodeid();

<<<<<<< HEAD
    printf("Destinaton id is %d\n",destination_id_);

=======
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
		send(
			MAC_BROADCAST,
			destination_id_,
			LEACH_DATA,
			sensedData_,
			dataSize,
			bsDist_,
			config_.bsCode_);

<<<<<<< HEAD
  	// //	if (!isClusterHead())
  	// 		//goToSleep();
    //
    //  printf("Clear sensed data of %d\n",sensor_node_->nodeid());
	 	clearSensedData();
=======
		if (!isClusterHead())
			goToSleep();

		clearSensedData();
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
	}

	if (xmitat + endFrmTime_ < nextChangeTime_ - 10 * config_.ssSlotTime_)
		Scheduler::instance().schedule(
			eventHandler_,
			new LeachEvent(&LeachAppWithResignation::sendDataToBS),
<<<<<<< HEAD
      //Scheduler::instance().clock() + xmitat);
      xmitat);

      //double energy_ = ((Battery *) sensor_node_->energy_model())->energy();
      //printf("Current energy: %f out of %f.\n", energy_, initial_energy_);

    // if (initial_energy_ == 0) {
    //   initial_energy_ = energy_;
    // }

    // if (isClusterHead()){ // && energy_ < initial_energy_ * 0.99) {
    // //if (isClusterHead()) {
    //   initial_energy_ = energy_;
    //
    //   Scheduler::instance().schedule(
    //    eventHandler_,
    //    new LeachEvent(&LeachAppWithResignation::challengeNodeAsNewClusterHead),
    //    xmitTime_);
    //   // Scheduler::instance().clock());
    //   //challegeNodeAsNewClusterHead();
    //   //  return;
    // }
  //	else
=======
      Scheduler::instance().clock() + xmitat);
      //xmitat);
>>>>>>> 700e6be944a45c491466040a8f54c333a4307495
}

void LeachAppWithResignation::sendMyDataToBS()
{
	sendDataToBS();
}

void LeachAppWithResignation::disseminateData(SensedData * data)
{
	if (data != NULL)
	{



		//printf("Common Node %d - Disseminating data -  Time %.3lf\n",sensor_node_->nodeid(),Scheduler::instance().clock());
		mergeSensedData(data);

		//printf(" - There is %d data aggregated.\n", sensedData_->count()); //sensedData_->getData().size());
	}
}


void LeachAppWithResignation::mergeSensedData(SensedData * data)
{

	AppDataList list;

	list = data->getData();

	for (AppDataList::iterator it = list.begin(); it != list.end(); it++)
		sensedData_->insertNewData(*it);
}

void LeachAppWithResignation::clearClusterChoices()
{
	for (CHs::iterator it = clusterChoices_.begin(); it != clusterChoices_.end(); it++)
	{
		chadv element = (chadv) *it;

		if (element.object != NULL)
			delete element.object;
	}

	clusterChoices_.clear();
}

void LeachAppWithResignation::clearSensedData()
{
	sensedData_->clear();
}
