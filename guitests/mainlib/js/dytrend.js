
function registratetrend(elem, tag) {
    var eltr = document.getElementById(elem);
    if (eltr!=null) {
        eltr.setAttribute('desc', tag);
        eltr.ontrend= testontrend;
    };
}
            
 
        
function testontrend(ev) {
              
    if (ev && (ev.length==2)){
        var ev0=ev[0];
        var elem=ev0.target;
        var datatrend=ev[1];
        if ((elem!=null) && (datatrend!=null)){
            if (elem.chart==null){
                var dt = [];
                var cnt = datatrend.length>1000 ? 1000 : datatrend.length;
                for (i = cnt; i >= 1; i--) { 
                    dt.push([ new Date(datatrend[datatrend.length-i][0] - 1000* 3600* 4),
                        (datatrend[datatrend.length-i][1])
                        ]);
                } 
                elem.data=dt;            
                elem.chart =new Dygraph(elem, dt,
                {
                    drawPoints: false,
                    showRoller: false,
                    valueRange: [0.0, 100.0],
                    labels: ['Time', 'Random']
                });                
            }
            else {
                elem.data.push([ new Date(datatrend[0][0] - 1000* 3600* 4), datatrend[0][1]]);
                elem.chart.updateOptions( {
                    'file': elem.data
                } );
                      
            }
        }
    }
}


