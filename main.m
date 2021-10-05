clc;

cst = actxserver('CSTStudio.Application');
project = cst.Active3D();
FarfieldPlot = invoke(project,'FarfieldPlot');
invoke(FarfieldPlot, 'SetCoordinateSystemType', 'ludwig2ae'); 
% Ön tarafa (-x) bakan antenler
invoke(FarfieldPlot,'Thetastart',-1,0,0);
invoke(FarfieldPlot,'Phistart',0,0,1);
% Arka tarafa (+x) bakan antenler
invoke(FarfieldPlot,'Thetastart',1,0,0);
invoke(FarfieldPlot,'Phistart',0,0,-1);
% Sol tarafa (-y) antenler
invoke(FarfieldPlot,'Thetastart',0,0,1);
invoke(FarfieldPlot,'Phistart',1,0,0);
% Sağ tarafa (+y) antenler
invoke(FarfieldPlot,'Thetastart',0,0,-1);
invoke(FarfieldPlot,'Phistart',-1,0,0);
invoke(FarfieldPlot,'ResetPlot');