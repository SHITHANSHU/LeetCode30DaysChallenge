var app = angular.module("testApp", ["ngRoute"]);
app.config(function($routeProvider) {
  $routeProvider
  .when("/", {
    resolve:{  
        check:function($location,user){
              if(localStorage.getItem("loggedin")){
                  $location.path("/control");
              }

          }
        },
    templateUrl : "login.html",
    controller : 'loginControl'
  })
    
  .when("/doc", {
    templateUrl : "doc.html"
  })
    

  .when("/user", {
      resolve:{  
    check:function($location,user){
          if(!localStorage.getItem("loggedin") ){
              $location.path("/");
          }
          if(localStorage.getItem("type")==0)
          {
              $location.path("/control");
          }
      }
    },
    templateUrl : "user.html",
    controller : 'testControl'
  })

  .when("/control", {
    resolve:{  
    check:function($location,user){
          if(!localStorage.getItem("loggedin") ){
              $location.path("/");
          }
          if(localStorage.getItem("type")==1)
          {
              $location.path("/user");
          }
      }
    },
    templateUrl : "front.html",
    controller : 'testControl'
  })

  
  .when("/tollbooth", {
    resolve:{  
    check:function($location,user){
          if(!localStorage.getItem("loggedin") ){
              $location.path("/");
          }
          if(localStorage.getItem("type")==1)
          {
              $location.path("/user");
          }
      }
    },
    templateUrl : "tollboothcontrol.html",
    controller : 'tollControl'
  })

  
  .when("/showexcept", {
    resolve:{  
    check:function($location,user){
          if(!localStorage.getItem("loggedin") ){
              $location.path("/");
          }
          if(localStorage.getItem("type")==1)
          {
              $location.path("/user");
          }
      }
    },
    templateUrl : "showexception.html",
    controller : 'showexceptcontrol'
  })
});


app.service('user',function(){
    var username;
    var loggedin=false;
    this.setname=function(name){
        username=name;
    } 
    this.getname=function(){
        return username;
    }
    this.userlogin=function(logedin)
    {
        loggedin=logedin;
    }
    this.isloggedin=function()
    {
        return loggedin;
    }
    var type;
    this.settype=function(name)
    {
        type=name;
    }
    this.gettype=function()
    {
        return type;
    }

    var unid;
    this.setid=function(name)
    {
        unid=name;
    }
    this.getid=function()
    {
        return unid;
    }
});

app.controller('loginControl',function($scope,$location,user, $http){

    $scope.invalidcred=false;
    $scope.loginchoice='admin';
    $scope.loginmain=function()
    {
        console.log("login stared");
        console.log($scope.loginchoice);

        var choi;
        if($scope.loginchoice=='admin')
        {
            choi=0;
        }
        else
        {
            choi=1;
        }
        var newurl="https://afternoon-mountain-79598.herokuapp.com/anpr/session/"+$scope.loguname+"/"+$scope.logpassword+"/"+choi;
        console.log(newurl);

        $http.get(newurl).then(
            function(response){

            $scope.data=response.data;

            if($scope.data.id!="&&invalid&&")
            {
                console.log("login sucessfull");
                user.setname($scope.data.id);
                user.userlogin(true);
                user.setid($scope.data.accessToken)
                localStorage.setItem('username',$scope.data.id);
                localStorage.setItem('loggedin',true);
                localStorage.setItem('accessToken',$scope.data.accessToken);
                localStorage.setItem('type',choi);
                
                if(choi==0)
                {$location.path("/control");
                
            }
            else
            {
                $location.path("/user");
            }
                
            }
            else
            {
                $scope.invalidcred=true;
                console.log("login unsucessfull");
                $location.path("/");
            }

            });



       
    }
});


app.controller('showexceptcontrol',function($scope,$location,user,$http,$interval)
{
 
    $scope.getExceptData=function()
    {
        console.log("function");
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getalltolldata").then(
            function(response){
                console.log(response.data);
            $scope.exeptdata=response.data;
            });
    }
    console.log("except")
    $scope.getExceptData();
});
app.controller('tollControl',function($scope,$location,user,$http,$interval)
{

    $scope.del=function(){
        localStorage.removeItem("username");
        localStorage.removeItem("loggedin");
        localStorage.removeItem("type");
        $location.path("/");
    }

    $scope.reset=function(){
        console.log("toll initiated")
        $scope.Submit="Submit";
        $scope.idReadOnly=false;
        $scope.id=null;
        $scope.type1=null;
        $scope.type2=null;
        $scope.type3=null;
        $scope.type4=null;
        $scope.type5=null;
        $scope.type6=null;
        $scope.datax=null;
        $scope.typer1=null;
        $scope.typer2=null;
        $scope.typer3=null;
        $scope.typer4=null;
        $scope.typer5=null;
        $scope.typer6=null;
        $scope.invalidtoll=false;
        $scope.invalidcode=false;
        $scope.numcode=null;
        $scope.loggedinas=user.getname();
        $scope.loggedinas=localStorage.getItem('username')
        $scope.canadd=false;
        $scope.candelete=false;
        $scope.exceptdata=null;
        $scope.numcode=null;
        $scope.exeptdata=null;
        $scope.refresh();
    }

    $scope.validnumcode=function()
    {
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/gettolldatabycode/"+$scope.id.toString();
        $http.get(url).then(
            function(response){
            $scope.exceptdata=response.data;
                var co=0;

                for(var d in $scope.exceptdata)
                {
                    console.log($scope.exceptdata[d].exception);
                    if($scope.exceptdata[d].exception.toString()==$scope.numcode.toString())
                    {   
                        co++;
                    }
               
                }

                if(co>0)
                {
                    $scope.canadd=false;
                    $scope.candelete=true;
                }
                else
                {
                    $scope.canadd=true;
                    $scope.candelete=false;
                }
            });
    }


    $scope.addtollexception=function()
    {
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/inserttolldata";
        url+="/"+$scope.id.toString();
        url+="/"+$scope.numcode.toString();
        $http.get(url).then(
            function(){
                $scope.reset();
            });
        
       
    }


    $scope.getExceptData=function()
    {
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getalltolldata").then(
            function(response){
            $scope.exeptdata=response.data;
            });
    }

    $scope.deletetollexception=function()
    {
        
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/inserttolldata";
        url+="/"+$scope.id.toString();
        url+="/"+$scope.numcode.toString();
        $http.get(url);
        $scope.reset();
    }

    $scope.addtolldata=function()
    {
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/addtollrecord";
        url += "/"+$scope.id.toString();
        url += "/"+$scope.type1.toString();
        url += "/"+$scope.type2.toString();
        url += "/"+$scope.type3.toString();
        url += "/"+$scope.type4.toString();
        url += "/"+$scope.type5.toString();
        url += "/"+$scope.type6.toString();
        url += "/"+$scope.typer1.toString();
        url += "/"+$scope.typer2.toString();
        url += "/"+$scope.typer3.toString();
        url += "/"+$scope.typer4.toString();
        url += "/"+$scope.typer5.toString();
        url += "/"+$scope.typer6.toString();

        $http.get(url).then(
            function(response){
            $scope.datax=response.data;
            $scope.reset()
            $scope.refresh()
            });
        

    }

    $scope.validatecode=function()
    {
        console.log("validing code");
        // $scope.refresh();
        var co=0;
        for(var d in $scope.datax)
        {
            console.log($scope.datax[d].code);
            if($scope.datax[d].code.toString()==$scope.id.toString())
            {
                co++;
            }
               
        }
        if(co==0)
        $scope.invalidcode=false;
        else
        $scope.invalidcode=true;
        console.log($scope.invalidcode)
    }

    $scope.validateToll1=function()
    {
        console.log("1,2,3");
        if($scope.type1<0 || $scope.type2<0 ||$scope.type3<0 ||$scope.type4<0 ||$scope.type5<0 ||$scope.type6<0)
        $scope.invalidtoll=true;
        else
        $scope.invalidtoll=false;
    }


    $scope.refresh=function(){
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getalltollrecorddata").then(
            function(response){
            $scope.datax=response.data;
            });

        
        
    }


    $scope.reset();
    console.log("test");
    $scope.refresh();

    $scope.editinit=function(ecode,type1,type2,type3,type4,type5,type6)
    {
       $scope.ide=ecode;
       $scope.typee1=type1;
       $scope.typee2=type2;
       $scope.typee3=type3;
       $scope.typee4=type4;
       $scope.typee5=type5;
       $scope.typee6=type6;
       console.log($scope.ide)
       console.log(ecode,type1,type2,type3,type4,type5,type6);
    }

    $scope.edit=function()
    {
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/updatetollrecord";
        url += "/"+$scope.ide.toString();
        url += "/"+$scope.typee1.toString();
        url += "/"+$scope.typee2.toString();
        url += "/"+$scope.typee3.toString();
        url += "/"+$scope.typee4.toString();
        url += "/"+$scope.typee5.toString();
        url += "/"+$scope.typee6.toString();
        console.log(url);
        $http.get(url).then(
            function(response){
            $scope.datax=response.data;
            $scope.ide=null;
            $scope.typee1=null;
            $scope.typee2=null;
            $scope.typee3=null;
            $scope.typee4=null;
            $scope.typee5=null;
            $scope.typee6=null;
            
            });
        $scope.reset();
    }
    $scope.initiateDelete=function(ecode)
    {
        $scope.id=ecode;
        console.log($scope.id);

    }

    $scope.terminateDelete=function()
    {
        $scope.id=null;
    }

    $scope.delete=function(ecode)
    {
        console.log($scope.id);
        var url="https://afternoon-mountain-79598.herokuapp.com/anpr/deletetollrecord";
        var del=$scope.id.toString()
        console.log(del.indexOf("ret"))
        if(del.indexOf("ret")!==-1)
        del=del.substr(3);
        url += "/"+del;
        $http.get(url).then(
            function(response){
            $scope.datax=response.data;
            });
        $scope.reset();
    }


});


app.controller('testControl',function($scope,$location,user,$http,$interval){

    
    $scope.reset=function(){
        $scope.Submit="Submit";
        $scope.idReadOnly=false;
        $scope.id=null;
        $scope.name=null;
        $scope.mobile=null;
        $scope.license=null;
        $scope.toll=null;
        $scope.type=null;
        $scope.disableSubmit=false;
        $scope.usedId=false;
        $scope.modalMessage="Insert Data";
        $scope.currentDeleteId=null;
        $scope.usedName=false;
        $scope.usedlicense=false;
        $scope.loggedinas=user.getname();
        $scope.loggedinas=localStorage.getItem('username')
        $scope.datalog=null;
        $scope.gotdata=false;
        $scope.nologdata=false;
    }

   
    $scope.reset();

    $scope.getfile=function(id)
    {
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getnocfile/"+id.toString(),{ responseType: 'arraybuffer' })
  .then(function(response) {
            var file = new Blob([response.data], { type: 'application/pdf' });
            var fileURL = window.URL.createObjectURL(file);
            var a = document.createElement("a");
            document.body.appendChild(a);
                a.href = fileURL;
                a.download = "noc"+id.toString()+".pdf";
                a.click();
        });
    }
    
    $scope.getlogdata=function()
    {
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getallcardata/"+$scope.id.toString()).then(
        function(response){
        $scope.datalog=response.data;
        console.log($scope.datalog)
        if($scope.datalog.length>0)
        $scope.gotdata=true;
        else
        $scope.nologdata=true;
        console.log()
        });
    }
    $scope.validateName=function(){
        


        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data3.length;i++)
        {
            if($scope.name==$scope.data3[i].uname)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedName=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedName=false;
            console.log("submit enabled");
        }
    }
    };

    $scope.validateName2=function(){
        


        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data3.length;i++)
        {
            if($scope.name==$scope.data3[i].uname && $scope.data3[i].type==1)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=false;
            $scope.usedName=false;
            console.log("submit enabled");
        }
        else
        {
            $scope.disableSubmit=true;
            $scope.usedName=true;
            console.log("submit disabled");
        }
    }
    };


    $scope.validateLicense=function(){
        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        
        for(var i=0;i<$scope.data.length;i++)
        {
            if($scope.license==$scope.data[i].license)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedlicense=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedlicense=false;
            console.log("submit enabled");
        }
    }
    };


    $scope.validateId=function(){
        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data.length;i++)
        {
            if($scope.id==$scope.data[i].id)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedId=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedId=false;
            console.log("submit enabled");
        }


        // $scope.changesub=false;
        // $scope.getfinalcardata=true;

        
    }
    };

    $scope.refresh=function(){

        console.log(localStorage.getItem('loggedin'))
        console.log(localStorage.getItem('username'))
        
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getall").then(
        function(response){
        $scope.data=response.data;
        });

        
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getalllogin").then(
        function(response){
        $scope.data3=response.data;
        console.log($scope.data3);
        });
    
    };

    $scope.numvali=function()
    {
        if($scope.search.mobile==null)
        {
            $scope.search.mobile=undefined;
        }
    }


    $scope.numvali2=function()
    {
        if($scope.search.toll==null)
        {
            $scope.search.toll=undefined;
        }
    }
    

    $scope.initiateDelete=function(sId){
        $scope.currentDeleteId=sId;
        console.log("initiated delete");
    };

    $scope.terminateDelete=function()
    {
        $scope.currentDeleteId=null;
    };

        $scope.delete=function(sId){
    
            console.log(sId);
            var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/delete/"+sId.toString();
            console.log(newUrl);
            $http.get(newUrl).then(
                function(response){
                $scope.data=response.data;
                });
            $scope.refresh();
        
            };

            $scope.editinit=function(sId){
    
                console.log(sId);
                var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/get/"+sId.toString();
                console.log(newUrl);
                $http.get(newUrl).then(
                    function(response2){
                        console.log(response2.data.id);    
                    $scope.data2=response2.data;
                    
                    $scope.id=$scope.data2.id;
                    $scope.name=$scope.data2.name;
                    $scope.mobile=$scope.data2.mobile;
                    $scope.toll=$scope.data2.toll;
                    $scope.type=$scope.data2.type;
                    $scope.license=$scope.data2.license;

                    $scope.idReadOnly=true;
                    $scope.Submit="Update"
                    
        $scope.modalMessage="Edit Data";
        console.log($scope.id);
        console.log($scope.name);
        console.log($scope.mobile);
        console.log($scope.toll);
        console.log($scope.license);
                    });
                    
                    $scope.refresh();
                };


    $scope.submit=function(){
        if($scope.idReadOnly)
        {
            $scope.update();

        }
        else
        {
            $scope.insert();
        }
        $scope.refresh();
    }


    $scope.update=function(){
        
        console.log($scope.id.toString());
        console.log($scope.name.toString());
        console.log($scope.toll.toString());
        console.log($scope.mobile.toString());
        console.log($scope.license.toString());
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/update/";
        
        newUrl+=$scope.id.toString();
        newUrl+="/"+$scope.license.toString();
        newUrl+="/"+$scope.mobile.toString();
        newUrl+="/"+$scope.name.toString();
        newUrl+="/"+$scope.toll.toString();
        newUrl+="/"+$scope.type.toString();
        console.log(newUrl);



        $http.get(newUrl).then(
            function(response){
            $scope.data=response.data;
            $scope.idReadOnly=false;
            $scope.Submit="Submit"
            
        $scope.modalMessage="Insert Data";
            $scope.reset();
            });

        $scope.refresh();
    }

    $scope.del=function(){
        localStorage.removeItem("username");
        localStorage.removeItem("loggedin");
        localStorage.removeItem("type");
        $location.path("/");
    }
    $scope.insert=function(){
        console.log($scope.id.toString());
        console.log($scope.name.toString());
        console.log($scope.toll.toString());
        console.log($scope.mobile.toString());
        console.log($scope.license.toString());
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/insert/";
        
        newUrl+=$scope.id.toString();
        newUrl+="/"+$scope.license.toString();
        newUrl+="/"+$scope.mobile.toString();
        newUrl+="/"+$scope.name.toString();
        newUrl+="/"+$scope.toll.toString();
        newUrl+="/"+$scope.type.toString();
        console.log(newUrl);



        $http.get(newUrl).then(
            function(response){
            $scope.data=response.data;
            $scope.reset();
            });

        $scope.refresh();
    }


    $scope.submitregister=function()
    {
        console.log($scope.name.toString());
        console.log($scope.cpass.toString());
        console.log($scope.loginchoice.toString());
        
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/insertlogin/";
        
        newUrl+=$scope.name.toString();
        newUrl+="/"+$scope.cpass.toString();
        var choi;
        if($scope.loginchoice=='admin')
        {
            choi=0;
        }
        else
        {
            choi=1;
        }
        newUrl+="/"+choi.toString();
        console.log(newUrl);



        $http.get(newUrl);

        $scope.refresh();
    }

   
    $scope.refresh();
//$interval($scope.refresh,1000);



});


app.controller('userControl',function($scope,$location,user,$http,$interval){

    $scope.getfile=function(id)
    {
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getnocfile/"+id.toString(),{ responseType: 'arraybuffer' })
  .then(function(response) {
            var file = new Blob([response.data], { type: 'application/pdf' });
            var fileURL = window.URL.createObjectURL(file);
            var a = document.createElement("a");
            document.body.appendChild(a);
                a.href = fileURL;
                a.download = "noc"+id.toString()+".pdf";
                a.click();
        });
    }
    
    $scope.reset=function(){
        $scope.Submit="Submit";
        $scope.idReadOnly=false;
        $scope.id=null;
        $scope.name=null;
        $scope.mobile=null;
        $scope.license=null;
        $scope.toll=null;
        $scope.type=null;
        $scope.disableSubmit=false;
        $scope.usedId=false;
        $scope.modalMessage="Insert Data";
        $scope.currentDeleteId=null;
        $scope.usedName=false;
        $scope.usedlicense=false;
        $scope.loggedinas=user.getname();
        $scope.loggedinas=localStorage.getItem('username');
        $scope.invaliddelete=false;
        $scope.currentDeleteToll=null;
        $scope.invalidtoll=false;
        $scope.invaliddelete=false;
        $scope.type=null;
    }

   
    $scope.reset();
    $scope.validateToll=function()
    {
        console.log("key")
        console.log($scope.toll);
 
            if($scope.toll<0)
            {
                $scope.disableSubmit=true;
               $scope.invalidtoll=true;
            }
            else
            {
                $scope.disableSubmit=false;
                $scope.invalidtoll=false;
            }
        
    
    }
    $scope.validateName=function(){
        


        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data3.length;i++)
        {
            if($scope.name==$scope.data3[i].uname)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedName=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedName=false;
            console.log("submit enabled");
        }
    }
    };

    $scope.validateName2=function(){
        


        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data3.length;i++)
        {
            if($scope.name==$scope.data3[i].uname && $scope.data3[i].type==1)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=false;
            $scope.usedName=false;
            console.log("submit enabled");
        }
        else
        {
            $scope.disableSubmit=true;
            $scope.usedName=true;
            console.log("submit disabled");
        }
    }
    };


    $scope.validateLicense=function(){
        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        
        for(var i=0;i<$scope.data.length;i++)
        {
            if($scope.license==$scope.data[i].license)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedlicense=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedlicense=false;
            console.log("submit enabled");
        }
    }
    };


    $scope.validateId=function(){
        if(!$scope.idReadOnly)
        {
        console.log("key pressed");
        var flag=0;
        for(var i=0;i<$scope.data.length;i++)
        {
            if($scope.id==$scope.data[i].id)
            flag=1;
        }


        if(flag==1)
        {
            $scope.disableSubmit=true;
            $scope.usedId=true;
            console.log("submit disabled");
        }
        else
        {
            $scope.disableSubmit=false;
            $scope.usedId=false;
            console.log("submit enabled");
        }
    }
    };

    $scope.refresh=function(){
    
        console.log("hi");
        console.log(localStorage.getItem('loggedin'))
        console.log(localStorage.getItem('username'))
        
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getallbyname/"+localStorage.getItem('username')).then(
        function(response){
        $scope.data=response.data;
        });

        
        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/getalllogin").then(
        function(response){
        $scope.data3=response.data;
        console.log($scope.data3);
        });
    
    };

    $scope.numvali=function()
    {
        if($scope.search.mobile==null)
        {
            $scope.search.mobile=undefined;
        }
    }


    $scope.numvali2=function()
    {
        if($scope.search.toll==null)
        {
            $scope.search.toll=undefined;
        }
    }
    

    $scope.initiateDelete=function(sId,toll){
        $scope.currentDeleteId=sId;
        $scope.currentDeleteToll=toll;
        console.log("initiated delete");
        $scope.deletemsg=" Are you Sure you want to delete data with Number Plate "+$scope.currentDeleteId+" ?";
        $scope.delbut="No";
        if(toll>0)
        {
            $scope.invaliddelete=true;
            $scope.deletemsg=" Cannot delete until toll is paid. Please pay the toll of Rs."+$scope.currentDeleteToll+" ";
            console.log("cannot delete");
            $scope.delbut="OK";
        }
    };

    $scope.terminateDelete=function()
    {
        $scope.currentDeleteId=null;
    };

    $scope.payToll=function()
    {
        $scope.getCar;

        $http.get("https://afternoon-mountain-79598.herokuapp.com/anpr/removetoll/"+$scope.getCar.toString()+"/"+$scope.toll+"/"+$scope.loggedinas).then(
            function(response){
            $scope.data=response.data;
            console.log($scope.data3);
            });


    }

    $scope.terminateDelete=function()
    {
        $scope.currentDeleteId=null;
        $scope.invaliddelete=false;
    };

        $scope.delete=function(sId){
    
            console.log(sId);
            


            if($scope.currentDeleteToll<=0)
            {
                var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/deleteuser/"+sId.toString()+"/"+$scope.loggedinas;
            console.log(newUrl);
            $http.get(newUrl).then(
                function(response){
                $scope.data=response.data;
                });
            $scope.refresh();
        }
        
            };

            $scope.editinit=function(sId){
    
                console.log(sId);
                var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/get/"+sId.toString();
                console.log(newUrl);
                $http.get(newUrl).then(
                    function(response2){
                        console.log(response2.data.id);    
                    $scope.data2=response2.data;
                    
                    $scope.id=$scope.data2.id;
                    $scope.name=$scope.data2.name;
                    $scope.mobile=$scope.data2.mobile;
                    $scope.toll=$scope.data2.toll;
                    
                    $scope.type=$scope.data2.type;
                    $scope.license=$scope.data2.license;

                    $scope.idReadOnly=true;
                    $scope.Submit="Update"
                    
        $scope.modalMessage="Edit Data";
        console.log($scope.id);
        console.log($scope.name);
        console.log($scope.mobile);
        console.log($scope.toll);
        console.log($scope.license);
        console.log($scope.type);
        console.log("tset")
                    });
                    
                    $scope.refresh();
              };


    $scope.submit=function(){
        if($scope.idReadOnly)
        {
            $scope.name=localStorage.getItem("username");
            $scope.update();

        }
        else
        {
            $scope.name=localStorage.getItem("username");
            $scope.insert();
        }
        $scope.refresh();
    }


    $scope.update=function(){
        
        $scope.name=localStorage.getItem("username");
        console.log($scope.id.toString());
        console.log($scope.name.toString());
        console.log($scope.toll.toString());
        console.log($scope.mobile.toString());
        console.log($scope.license.toString());
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/updateuser/";
        
        newUrl+=$scope.id.toString();
        newUrl+="/"+$scope.license.toString();
        newUrl+="/"+$scope.mobile.toString();
        newUrl+="/"+$scope.name.toString();
        newUrl+="/"+$scope.toll.toString();
        newUrl+="/"+$scope.type.toString();
        console.log(newUrl);



        $http.get(newUrl).then(
            function(response){
            $scope.data=response.data;
            $scope.idReadOnly=false;
            $scope.Submit="Submit"
            
        $scope.modalMessage="Insert Data";
            $scope.reset();
            });

        $scope.refresh();
    }

    $scope.del=function(){
        localStorage.removeItem("username");
        localStorage.removeItem("loggedin");
        // localStorage.setItem("loggedin",false);
        // localStorage.setItem("username","&&invalid&&");
        // localStorage.removeItem("type");
        
        $location.path("/");
    }
    $scope.insert=function(){
        
        $scope.name=localStorage.getItem("username");
        console.log($scope.id.toString());
        console.log($scope.name.toString());
        console.log($scope.toll.toString());
        console.log($scope.mobile.toString());
        console.log($scope.license.toString());
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/insertuser/";
        
        newUrl+=$scope.id.toString();
        newUrl+="/"+$scope.license.toString();
        newUrl+="/"+$scope.mobile.toString();
        newUrl+="/"+$scope.name.toString();
        newUrl+="/"+$scope.toll.toString();
        newUrl+="/"+$scope.type.toString();
        console.log(newUrl);



        $http.get(newUrl).then(
            function(response){
            $scope.data=response.data;
            $scope.reset();
            });

        $scope.refresh();
    }


    $scope.submitregister=function()
    {
        console.log($scope.name.toString());
        console.log($scope.cpass.toString());
        console.log($scope.loginchoice.toString());
        
        var newUrl="https://afternoon-mountain-79598.herokuapp.com/anpr/insertlogin/";
        
        newUrl+=$scope.name.toString();
        newUrl+="/"+$scope.cpass.toString();
        var choi;
        if($scope.loginchoice=='admin')
        {
            choi=0;
        }
        else
        {
            choi=1;
        }
        newUrl+="/"+choi.toString();
        console.log(newUrl);



        $http.put(newUrl);

        $scope.refresh();
    }

   
    $scope.refresh();
//$interval($scope.refresh,1000);



});

