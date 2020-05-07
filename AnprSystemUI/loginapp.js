var app=angular.module('testApp',['ngRoute']);


//     app.config(function($routeProvider){
//         $routeProvider
//         .when('/',{
//             templateUrl:'login.html'
//         })
//         .when('/control',{
//             templateUrl:'front.html'
//         })
//         .otherwise({
//             redirectTo:'/'
//         });
    
//     });

app.controller('testControl',function($scope,$http,$interval){

    var name=$scope.uname;
    var pass=$scope.pass;
$scope.login=function()
{
    console.log("login");
    if($scope.uname == 'test' && $scope.pass=="test")
    {
        $location.path('/control')
    }
}
});