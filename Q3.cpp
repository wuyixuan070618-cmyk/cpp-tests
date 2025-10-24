#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <map>
using namespace std;
class Spaceship{
    public:
        string model;
        Spaceship()=default;
        Spaceship(string m,double s,double e):model(m),speed(s),energy(e){}
        virtual inline Spaceship &showStats(){cout<<"Model:"<<model<<" Speed:"<<speed<<" Energy"<<energy<<endl;return *this;}
        virtual Spaceship &action()=0;
    protected:
        double speed;
        double energy;
};
class Cargoship:public Spaceship{
    private:
        int cargoCapacity;
        int cargoLoaded = 0;
    public:
        Cargoship()=default;
        Cargoship(string m,double s,double e,int c):Spaceship(m,s,e),cargoCapacity(c){}
        inline Cargoship &action(){cout<<model<<"-Loading cargo!"<<endl;return *this;}
        Cargoship &loadCargo(int cargo){
            if(cargo+cargoLoaded>cargoCapacity)cout<<model<<"-Overweight!"<<endl;
            else{
                cargoLoaded+=cargo;
                cout<<model<<"-Remaining capacity:"<<cargoCapacity-cargoLoaded<<endl;
            }
            return *this;
        }
};
class Battleship:public Spaceship{
    private:
        int weaponPower;
    public:
        Battleship()=default;
        Battleship(string m,double s,double e,int w):Spaceship(m,s,e),weaponPower(w){}
        inline Battleship &action(){cout<<model<<"-Ready to fire laser!"<<endl; return *this;}
        Battleship &fireLaser(){
            if(energy-weaponPower<0)cout<<model<<"-Running out of energy!"<<endl;
            else{
                energy-=weaponPower;
                cout<<model<<"-Done "<<weaponPower<<" damage to enermy!"<<endl;
            }
            return *this;
        }
};
class Exploreship:public Spaceship{
    private:
        int scanRange;
    public:
        Exploreship()=default;
        Exploreship(string m,double s,double e,int sc):Spaceship(m,s,e),scanRange(sc){};
        inline Exploreship &action(){cout<<model<<"-Scanning planet..."<<endl; return *this;}
        Exploreship &scanPlanet(int planetSize){
            int range=0;
            cout<<model<<"-Attempting to scan the planet..."<<endl;
            while(range<=planetSize){
                if(energy-scanRange*0.5<0){cout<<"-Running out of energy!Scanning FAILED;"<<endl;return *this;}
                else{
                    this_thread::sleep_for(chrono::seconds(3));
                    cout<<model<<"-Scanning...Process:"<<(range*1.0/planetSize*1.0)*100<<"%"<<endl;
                    energy-=scanRange*0.5;
                    range+=scanRange;
                }
            }
            cout<<model<<"-Scanning COMPLETE!"<<endl;
            return *this;
        }
};
class SpaceshipFleet{
    private:
        vector<Cargoship> cargoFleet;
        vector<Battleship> battleFleet;
        vector<Exploreship> exploreFleet;
        map<int ,string> typeMap;
    public:
        SpaceshipFleet(){
        typeMap[1]="cargo capacity";
        typeMap[2]="weapon power";
        typeMap[3]="scan range";
        }
        SpaceshipFleet &add_ship()
        {
            int choice;
            cout<<"Please enter the type of the spaceship you'd like to add to your fleet(1-Cargoship,2-Battleship,3-Exploreship):";
            cin>>choice;
            string m;
            double s,e;
            int sp;
            cout<<"Please enter the value of the attributes of your new ship(model,speed,energy and "<<typeMap[choice]<<"):"<<endl;
            cin>>m>>s>>e>>sp;
            switch (choice){
            case 1:
                cargoFleet.push_back(Cargoship(m,s,e,sp));
                cout<<"System-New cargoship added to your fleet!"<<endl;
                break;
            case 2:
                battleFleet.push_back(Battleship(m,s,e,sp));
                cout<<"System-New battleship added to your fleet!"<<endl;
                break;
            case 3:
                exploreFleet.push_back(Exploreship(m,s,e,sp));
                cout<<"System-New exploreship added to your fleet!"<<endl;
                break;
            default:
                cout<<"System:Your choice should be 1,2 or 3!"<<endl;
                break;
            }
            return *this;
        }
        SpaceshipFleet &show_fleet(){
            cout<<"Number of cargoships:"<<cargoFleet.size()<<endl;
            cout<<"Number of battleships:"<<battleFleet.size()<<endl;
            cout<<"Number of expolreships:"<<exploreFleet.size()<<endl;
            return *this;
        }
        SpaceshipFleet &rent_ship(){
            int type;
            string model;
            cout<<"Please choose the type of the spaceship you'd like to rent(1-Cargoship,2-Battleship,3-Exploreship):";
            cin>>type;
            cout<<"Please input the model of the spaceship you'd like to rent:";
            cin>>model;
            switch (type){
            case 1:
                for(unsigned int i = 0,cargo;i < cargoFleet.size();i++){
                    if(model==cargoFleet[i].model)
                    {
                        cargoFleet[i].action();
                        cout<<"Please enter the weight of the cargo:";
                        cin>>cargo;
                        cargoFleet[i].loadCargo(cargo);
                        return *this;
                    }
                }
                cout<<"System-"<<model<<" unfound!"<<endl;
                break;
            case 2:
                for(unsigned int i = 0;i < battleFleet.size();i++){
                    if(model==battleFleet[i].model)
                    {
                        battleFleet[i].action();
                        battleFleet[i].fireLaser();
                        return *this;
                    }
                }
                cout<<"System-"<<model<<" unfound!"<<endl;
                break;
            case 3:
                for(unsigned int i = 0,planetSize;i < exploreFleet.size();i++){
                    if(model==exploreFleet[i].model)
                    {
                        exploreFleet[i].action();
                        cout<<"Please enter the size of the planet:";
                        cin>>planetSize;
                        exploreFleet[i].scanPlanet(planetSize);
                        return *this;
                    }
                }
                cout<<"System-"<<model<<" unfound!"<<endl;
                break;
            default:
                cout<<"System-Your choice should be 1,2 or 3!"<<endl;
                break;
            }
            return *this;
        }
};

int main()
{
    int choice;
    SpaceshipFleet Fleet;
    while(choice !=4){ 
        cout<<"You can chooose the operation from"<<endl<<"1-add a spaceship"<<endl<<"2-rent a spaceship"<<endl<<"3-show info"<<endl<<"4-quit the program:";
        cin>>choice;
        switch (choice)
        {
        case 1:
            Fleet.add_ship();
            break;
        case 2:
            Fleet.rent_ship();
            break;
        case 3:
            Fleet.show_fleet();
            break;
        default:
            break;
        }
    }
    return 0;
}