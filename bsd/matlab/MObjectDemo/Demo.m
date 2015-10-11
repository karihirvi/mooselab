classdef Demo < handle
%DEMO MObjectDemo project main class
%   

properties
  clients = Client.empty(1,0)
  server
end

methods
  function self = Demo()
    persistent pathSet
    if isempty(pathSet)
      p = strsplit(mfilename('fullpath'), filesep);
      p2 = p(1:end-2);
      addpath(strjoin(p2, filesep));
      pathSet = true;
    end
    client_1 = Client('client_1');
    client_2 = Client('client_2');
    srv = Server;
    srv.connect('no params', @client_1.slotNoParams);
    srv.connect('no params', @client_2.slotNoParams);
    srv.connect('with params', @client_1.slotWithParams);
    self.server = srv;
    self.clients(end+1) = client_1;
    self.clients(end+1) = client_2;
  end
  
  function doEmit(self)
    self.server.emitWithNoParameters();    
    self.server.emitWithParameters();
  end
end
  
end

