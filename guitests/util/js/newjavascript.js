// report_controller


  
dbutil.report_controller = function(){
    try{

        this.items = [];
        this.base={}; 
        this.xmllist = dbutil.database.getXMLData(this, 'ReportList');
        this.connect();
    }
    catch(error){      
        dbutil.database.modal(dbutil.database.FATAL, error);
    }  
};


dbutil.report_controller.MAX_PERIOD = 360000000;

dbutil.report_controller.MIN_PERIOD = 60000;

dbutil.report_controller.MID_PERIOD = 10800000;


dbutil.report_controller.prototype.connect = function(noinit){
    try{
        var ts = this;
        this.xml= [];
        var ts = this;
        this.xml= []; 
        this.base = {};
        this.items=[];
        this.connection = undefined;            
        if (!noinit){ 
            this.init();}
        else{
            //this.updateselect();
            this.updatelist();
            this.setselectpanel(false);}
        //this.setStart(new Date('Sep 10 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        this.setStart(new Date((new Date()).valueOf() - dbutil.report_controller.MID_PERIOD));
        this.setStop(new Date());        
        this.updatedate();       
        window.$$connectSCDB( 
            function(){
                var evnt= event;
                setTimeout( function(){
                    ts.attach(evnt);
                },0)
            },
            ts.provider, ts.connectionstring);
        dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_CONNECTING);
    }
    catch(error){      
        dbutil.database.modal(dbutil.database.FATAL, error);
    }  
};


dbutil.report_controller.prototype.attach = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    window.reportcontroller = this;
    this.connection = ev.connection;
    this.inittags(ev.tags);
    this.parseXMLData();
    if (!this.xml.length){
        dbutil.database.modal(dbutil.database.FATAL, dbutil.database.ERROR_WR_APPTRINFO  + dbutil.database.APPINFOFILE);
        return;
    }
    this.updatelist();

    this.requested=false;
    this.setstate(); 
    dbutil.database.clearmodal();
    
}



dbutil.report_controller.prototype.parseXMLData = function(){
    this.xml=[];
    var j=0;
    for(var e=this.xmllist.firstElementChild; e; e=e.nextElementSibling){
        var lst= e.getAttribute("name");                       
        for(var el=e.firstElementChild; el; el=el.nextElementSibling){
            var arr= el.getAttribute("name");
            var delt = et.getAttribute("delt") ? et.getAttribute("delt") : 0;
            var group = et.getAttribute("group") ? et.getAttribute("group") : 1;
            var sum = et.getAttribute("sum") ? et.getAttribute("sum") : 1;
            var type = et.getAttribute("type") ? et.getAttribute("type") : 0;  
            var initperiod = et.getAttribute("initperiod") ? et.getAttribute("initperiod") : 1;
            var subperiod = et.getAttribute("subperiod") ? et.getAttribute("subperiod") : 0;            
            var tags=[];
            for(var et=el.firstElementChild; et; et=et.nextElementSibling){                               
                var tg = et.getAttribute("tg");
                var color = et.getAttribute("color");
                var sumtype = et.getAttribute("sumtype") ? et.getAttribute("sumtype") : 1;
                var round = et.getAttribute("round") ? et.getAttribute("round") : 0;
                if (/*this.base[tg]*/true)
                        tags.push({
                        tag: tg,
                        color: color,
                        sumtype: sumtype,
                        round: round
                    })                         
            }
            this.xml.push({
                list: lst,
                name: arr,
                delt: delt,
                group: group,
                sum: sum,
                type: type,
                initperiod: initperiod,
                subperiod: subperiod,
                tags: tags
            });            
        }
    }   
}



dbutil.report_controller.prototype.inittags = function(val){
    this.base = {};
    for (var i=0;i<val.length;++i){
        this.base[val[i].name] = val[i];
    }
}


dbutil.report_controller.prototype.init = function(){
    
    dbutil.database.datepickerset();
                         
    $('body').layout({ 
        north__size:			32 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
        ,	
        north__spacing_open:	        0
                    
    });   
                
    $("#inner").layout({
        south__size:			200 
        ,	
        spacing_open:			0 
        ,	
        spacing_closed:			0 
    }); 
                
    var ts=this;    
    
    $( "#run-button" ).button({
        text: false,
        disabled: true,
        icons: {
            primary: "ui-icon-arrowrefresh-1-w"
        }
    }).click(function() {
        window.reportcontroller.run();
    ;
    })

    $( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.reportcontroller.resetselectpanel();
    ;
    });
    
    $( "#noparam-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-0"
        }
    }).click(function() {
        window.reportcontroller.removeall();
    ;
    });    
    
    
    $( "#left-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-w"
        }
    }).click(function() {
        window.reportcontroller.setLeft();
    });
    
    $( "#right-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.reportcontroller.setRight();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.reportcontroller.setNow();
    ;
    });  
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.reportcontroller.setNow();
    ;
    });     


    $("#select-panel-report" ).position({
        of: $( "#top-menuemain" ),
        my: 'left bottom',
        at: 'left top'
    });    
    
    this.setselectpanel(false);
    
    var panelheight = $("#select-panel-report" )[0].getClientRects ? $("#select-panel-report" )[0].getClientRects()[0].height : undefined;
    var bottomheight = $("#select-table-bottom" )[0].getClientRects ? $("#select-table-bottom" )[0].getClientRects()[0].height : undefined;
    
    this.startpicker = $('#starttime').datetimepicker({
        onClose:  function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStart(dt);
        }
    }).click(function(){ts.setselectpanel(false);});
    this.stoppicker = $('#stoptime').datetimepicker({
        onClose: function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStop(dt);
        }
    }).click(function(){ts.setselectpanel(false);});;  
    
    
    this.listgrid = $("#list").jqGrid({
        data: this.xml,
        autowidth: true,
        datatype: "local",
        height: panelheight ? panelheight : 'auto',
        scrollrows: true,
        shrinkToFit: true,
        cellLayout: 1,
        colNames:['list','Наименование'],     
        onSelectRow: function (rowId, status, e) {
            var row = $("#list").jqGrid('getRowData',rowId);
            if (status) {
                ts.add(row.tag);
                ts.selectedid[rowId]=true;
            }
            else
            {
                ts.remove(row.tag, rowId);
                ts.selectedid[rowId]=false;
            }
          
        },
        colModel:[
        {
            name:'list',
            index:'list',  
            width:1, 
            hidden: true
        },
        {
            name:'name',
            index:'name', 
            width:1, 
            hidden: true
        }
        
    
		
        ],
        rowNum: 100000,
        //treeIcons: {plus:'ui-icon-circle-arrow-e',minus:'ui-icon-triangle-1-s',leaf:'ui-icon-radio-off'},
   	hidegrid: false,
        viewrecords: true,
        grouping:true,
        groupingView : {
            groupField : ['list'],
            groupSummary : [false],
            groupColumnShow : [false],
            groupText : ['<b>{0}</b>'],
            groupCollapse : true,
            groupOrder: ['asc'],
            groupCollapse: true
        },
        
        caption: 'Выбор отчета'
   	
    });
    

    
    
                              
}; 



   


dbutil.report_controller.prototype.add = function(tag){
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==tag)
            return false;
    }
    if (this.base[tag]){
        this.items.push({
            oprt : '',            
            id : tag, 
            comment : this.base[tag].comment, 
            eu : this.base[tag].eu,  
            mineu : this.base[tag].mineu,  
            maxeu : this.base[tag].maxeu,
            color: this.selectcolor(),
            coloredit: '',
            auto: true,
            autoedit: '',
            rangeedit: '',
            min: this.base[tag].mineu,
            max: this.base[tag].max,
            range: (this.base[tag].mineu + ' - ' + this.base[tag].maxeu),
            selectrange: '',
            datarange: ''
        });
        this.updateselect();                
        return true;
    }
    return false;    
}


dbutil.report_controller.prototype.remove= function(id, exclude){
    var fnd = null;
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            fnd=i;
            break;
        }
    }
    if (fnd===null) return false;         
    var ids = $("#list").jqGrid('getDataIDs');
    for(var i=0;i < ids.length;i++){
        var row = $("#list").jqGrid('getRowData',ids[i]);
        if (row && row.tag==id && (ids[i]!=exclude) && this.selectedid[ids[i]]) {
            this.selectedid[ids[i]]=false;
            $("#list").jqGrid('setSelection',ids[i],false);
        }
    }
    libutil.util.remove_element_arr(this.items,fnd);
    this.range[id] = undefined;
    this.datarange[id] = undefined;    
    this.updateselect();
    this.pugerange();
    return true;      
}

dbutil.report_controller.prototype.removeall= function(){
    //for (var j=0;j<this.items.length;++j){
    $("#list").jqGrid('resetSelection');
 
    this.items = [];
    this.range = {};
    this.datarange = {}; 
    //this.updateselect();
    this.pugerange();        
}

dbutil.report_controller.prototype.selectcolor = function(){
    var result = 'FF0000';
    var j=0;
    while (j<dbutil.report_controller.COLORS.length){
        var fnd = false;
        for (var i=0;i<this.items.length;++i){
            if (this.items[i].color==dbutil.report_controller.COLORS[j])
                fnd = true;
        }
        if (!fnd) return dbutil.report_controller.COLORS[j];
        j++;
    }
    return result;
}


dbutil.report_controller.prototype.updatedataextremes = function(){
    for (var i=0;i<this.items.length;++i){
        var id = this.items[i].id;
        var ext=null;//this.trendchart ? this.trendchart.getExtremes(id) : null;
        this.datarange[id] = ext ? {
            min : ext.dataMin,
            max : ext.dataMax
        } : undefined;
                   
        this.items[i].datarange= ext && (ext.dataMax || ext.dataMax===0) && (ext.dataMin || ext.dataMin===0) ? 
        (ext.dataMin.toFixed(2)  + ' - ' + ext.dataMax.toFixed(2)) : '';                                         
    }  
    //this.updateselect(); 
}



dbutil.report_controller.prototype.updatelist = function( req ) {
    $("#list").jqGrid('clearGridData');
    //for (var i=0;i<this.xml.length;++i)
    //    this.xml[i].rowid=(i+1).toString();
    //    $("#list").jqGrid('addRowData',(i+1).toString(),this.xml[i]); 
        $("#list").jqGrid('addRowData',"rowid",this.xml);   
        $("#list").trigger("reloadGrid");
}


    
dbutil.report_controller.prototype.tags = function(){
    var rslt = [];
    for (var i=0;i<this.items.length;++i)
        rslt.push(this.items[i].id);   
    return rslt;
}  



dbutil.report_controller.prototype.run = function(){
    this.setselectpanel(false);
    dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_DATAREQUEST );
    var ts = this;
    ts.requested=true;
    ts.setstate();   
}


dbutil.report_controller.prototype.setStart = function(val){
    dbutil.database.setStart(val, this, dbutil.report_controller.MIN_PERIOD, dbutil.report_controller.MAX_PERIOD);
}

dbutil.report_controller.prototype.setStop = function(val){
    dbutil.database.setStop(val, this, dbutil.report_controller.MIN_PERIOD, dbutil.report_controller.MID_PERIOD , dbutil.report_controller.MAX_PERIOD);
}

dbutil.report_controller.prototype.setLeft = function(){
    dbutil.database.setLeft(this);
}

dbutil.report_controller.prototype.setRight = function(){
    dbutil.database.setRight(this);
}

dbutil.report_controller.prototype.setNow = function(){
    dbutil.database.setNow(this);
}

dbutil.report_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

dbutil.report_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}



dbutil.report_controller.prototype.setselectpanel = function(val){
    var panel = $( "#select-panel-report" )[0];
    panel.className = val ? 'ui-widget-content select-panel-visible' : 'ui-widget-content select-panel-hidden';
    panel.visibility = val ? true : false;   
}

dbutil.report_controller.prototype.resetselectpanel = function(){
    var panel = $( "#select-panel-report" )[0];
    this.setselectpanel(!panel.visibility);    
}


dbutil.report_controller.prototype.setstate = function(){
    $( "#run-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#left-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#right-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");    
    $( "#select-button" ).button((this.xml.length) ? "enable"  : "disable");
    $( "#noparam-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#print-button" ).button((false) ? "enable"  : "disable");
    if (!this.items.length && this.xml.length)
        this.setselectpanel(true);
}
