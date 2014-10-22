
Highcharts.setOptions({
    global: {
        useUTC: false
    }
});
                        

        
function registratetrend(elem, tag) {
    var eltr = document.getElementById(elem);
    if (eltr!=null) {
        eltr.setAttribute('desc', tag);
        window.addTrendsListener(function(){testontrend(event);} );
    };

}
            
 
        
function testontrend(ev) {
    if (ev && (ev.length==2)){
        var ev0=ev[0];
        var elem=ev0.target;
        var datatrend=ev[1];
        if ((elem!=null) && (datatrend!=null)){
            if (elem.chart==null){
                elem.chart = new Highcharts.Chart({
                    chart: {
                        renderTo: elem.id ,
                        defaultSeriesType: 'line',
                        marginRight: 10,
                        backgroundColor: "#EEEEEE",
                        borderColor: "#111111",
                        events: {
                            load: testontrend 
                        }
                    },
                    title: {
                        text:  elem.getAttribute('desc')
                    },
                    xAxis: {
                        type: 'datetime',
                        tickPixelInterval: 105,
                        plotLines: [{
                            value: 1,
                            width: 1,
                            color: '#808080'
                        }],
                        gridLineWidth : 1
                    },
                    yAxis: {
                        title: {
                            text: 'Value'
                        },
                        plotLines: [{
                            value: 0,
                            width: 1,
                            color: '#808080'
                        }]
                    },
                    tooltip: {
                        formatter: function() {
                            return '<b>'+ this.series.name +'</b><br/>'+
                            Highcharts.dateFormat('%H:%M:%S', this.x) +'<br/>'+ 
                            Highcharts.numberFormat(this.y, 2);
                        }
                    },
                    legend: {
                        enabled: false
                    },
                    exporting: {
                        enabled: false
                    },
                    plotOptions: {
                        series: {
                            marker: {
                                enabled: false,
                                states: {
                                    hover: {
                                        enabled: true,
                                        radius: 3
                                    }
                                }
                            }
                        },
                        line: {
                            lineWidth: 1,
                            color: '#FF0000'
                        }
                    },
                    series: [{
                        name: elem.desc,
                        data: (function() {		
                            var cnt = datatrend.length>10000 ? 10000 : datatrend.length;
                            var data = [];
							
                            for (i = cnt; i >= 1; i--) { 
                                data.push({
                                    x: (datatrend[datatrend.length-i][0]),
                                    y: (datatrend[datatrend.length-i][1])
                                });
                            }                                                       
                            return data;
                        })()
                    }]
                });                  
            }
            else {
                var series = elem.chart.series[0];
                series.addPoint([(datatrend[0][0]), datatrend[0][1]], true, true);
                      
            }

        }
    }
}
