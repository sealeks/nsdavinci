// database

dbutil = {};

dbutil.database = {};

dbutil.database.APPINFOFILE = 'AppMetaInfo.xml';

dbutil.database.ERROR_NO_APPINFO = "Нет файла описания ";

dbutil.database.ERROR_WR_APPINFO = "Неверный формат ";

dbutil.database.ERROR_WR_APPTRINFO = "Несовпадение таблицы индексов и описания ";

dbutil.database.MESSAGE_CONNECTING = "Установка соединения";

dbutil.database.MESSAGE_DATAREQUEST = "Запрос данных";

dbutil.database.FATAL = 2;

dbutil.database.RETRY = 1;

dbutil.database.PROCCESS = 0;


dbutil.database.getXMLData = function(obj, root){
    
    var doc = libutil.dom.readDoc(dbutil.database.APPINFOFILE); 
    
    if (!doc) throw dbutil.database.ERROR_NO_APPINFO  + dbutil.database.APPINFOFILE;
             
    
    var rootel = doc.getElementsByTagName('meta');
    
    if (!rootel || !rootel.length) throw (dbutil.database.ERROR_WR_APPINFO + dbutil.database.APPINFOFILE);
    
    rootel=rootel[0];
    
    obj.connectionstring = rootel.getAttribute("constring");
    
    obj.provider = rootel.getAttribute("DBProvider").valueOf();

    if (!obj.connectionstring || !obj.provider) throw (dbutil.database.ERROR_WR_APPINFO  + dbutil.database.APPINFOFILE);
               
    var els = doc.getElementsByTagName(root);
    
    if (!els || !els.length) throw (dbutil.database.ERROR_WR_APPINFO  + dbutil.database.APPINFOFILE);
    
    return els[0];
                  
};

dbutil.database.reportError = function(ev, obj, noinit){
        switch(ev.error){
            case 2049: {
                var ts = obj;
                dbutil.database.modal(dbutil.database.RETRY, ev.what, function(){
                    dbutil.database.clearmodal();
                    ts.connect(noinit)
                });
                break;
            }
            default: {
                dbutil.database.modal(dbutil.database.FATAL, ev.what);    
            }
        }
        return;
}

dbutil.database.modal = function(state, message, call){
    dbutil.database.clearmodal();
    switch(state){
        case dbutil.database.FATAL:{
            if (document.getElementById('alerttext')) document.getElementById('alerttext').textContent=message ? message: ''; 
            $('#runmodalalert').dialog({
                modal: true, 
                resizable: false,
                closeOnEscape: false, 
                disabled: true, 
                title: "Фатальная ошибка", 
                dialogClass: "alert",  
                buttons: {
                    "Выход": function() {
                        document.close();
                    }
                }
            });
            break;
        }
        case dbutil.database.RETRY:{
    
            if (document.getElementById('alerttext')) document.getElementById('alerttext').textContent=message ? message: ''; 
            $('#runmodalalert').dialog({
                modal: true, 
                resizable: false, 
                closeOnEscape: false, 
                disabled: true, 
                title: "Oшибка", 
                dialogClass: "alert",  
                buttons: {
                    "Выход": function() {
                        document.close();
                    }, 
                    "Повторить" :  call
                }
            });
            break;
        }
        default:{
            $('#runmodal').dialog({
                modal: true, 
                resizable: false, 
                closeOnEscape: false, 
                disabled: true, 
                title: message
            });     
        }    
    }
}

dbutil.database.clearmodal = function(){
    $('#runmodal').dialog('close');
    $('#runmodalalert').dialog('close');
    $('#runmodal').dialog('destroy');
    $('#runmodalalert').dialog('destroy');
}

dbutil.database.datepickerset = function(){
    $.datepicker.regional['ru'] = {
        closeText: 'Закрыть',
        prevText: '<Пред',
        nextText: 'След>',
        currentText: 'Сегодня',
        monthNames: ['Январь','Февраль','Март','Апрель','Май','Июнь',
        'Июль','Август','Сентябрь','Октябрь','Ноябрь','Декабрь'],
        monthNamesShort: ['Янв','Фев','Мар','Апр','Май','Июн',
        'Июл','Авг','Сен','Окт','Ноя','Дек'],
        dayNames: ['воскресенье','понедельник','вторник','среда','четверг','пятница','суббота'],
        dayNamesShort: ['вск','пнд','втр','срд','чтв','птн','сбт'],
        dayNamesMin: ['Вс','Пн','Вт','Ср','Чт','Пт','Сб'],
        weekHeader: 'Не',
        dateFormat: 'dd.mm.yy',
        firstDay: 1,
        isRTL: false,
        showMonthAfterYear: false,
        yearSuffix: ''
    };
                
    $.datepicker.setDefaults($.datepicker.regional['ru']);

          
    $.timepicker.regional['ru'] = {
        timeOnlyTitle: 'Выберите время',
        timeText: 'Время',
        hourText: 'Часы',
        minuteText: 'Минуты',
        secondText: 'Секунды',
        millisecText: 'миллисекунды',
        currentText: 'Сейчас',
        closeText: 'Закрыть',
        ampm: false
    };
    $.timepicker.setDefaults($.timepicker.regional['ru']);
}


dbutil.database.setStart = function(val, self, min, max){
    if (self.start != val){
        if (self.stop  && self.start){
            var period = (self.stop.valueOf()-self.start.valueOf());
            var potperiod = (self.stop.valueOf()-val.valueOf());
            if (potperiod>min){
                if (potperiod>max)
                    self.stop=new Date(val.valueOf() + max);  
                self.start=val;
            }
            else{
                self.start=val;
                self.stop = new Date(val.valueOf() + min);
            }         
            self.normalizePeriod();
        }
        else{
            self.start=val;
            self.normalizePeriod();
        }
    }
}

dbutil.database.setStop = function(val, self, min, mid, max ){
    if (self.stop!= val){
        if (self.stop  && self.start){
            var period = (self.stop.valueOf()-self.start.valueOf());
            var potperiod = (val.valueOf()-self.start.valueOf());
            if (potperiod>min){
                if (potperiod>max)
                    self.start=new Date(val.valueOf() - max);  
                self.stop=val;
            }
            else{
                self.stop=val;
                self.start = new Date(val.valueOf() - mid);
            }         
            self.normalizePeriod();
        }
        else{
            self.stop=val;
            self.normalizePeriod();
        }
    }
}

dbutil.database.setLeft = function(self){
    var period = (self.stop.valueOf()-self.start.valueOf());
    self.start=new Date(self.start.valueOf() - period);
    self.stop=new Date(self.stop.valueOf() - period); 
    self.normalizePeriod();
    //self.run();
}

dbutil.database.setRight = function(self){
    var period = (self.stop.valueOf()-self.start.valueOf());
    if ((new Date()).valueOf()<self.stop.valueOf()) {
       self.start=new Date((new Date()).valueOf() - period);
       self.stop=new Date(self.start.valueOf() + period);         
    }
    else{
       self.start=new Date(self.start.valueOf() + period);
       self.stop=new Date(self.stop.valueOf() + period);        
    }
    self.normalizePeriod();
    //self.run();
}

dbutil.database.setNow = function(self, per){
    var period = per ? per : (self.stop.valueOf()-self.start.valueOf());
    self.start=new Date((new Date()).valueOf() - period);
    self.stop=new Date(self.start.valueOf() + period);         
    self.normalizePeriod();
    //self.run();
}

dbutil.database.date = function(date){
    var d = date.getDate();
    var m = date.getMonth()+1;
    var y = date.getFullYear();
    return '' + y +'-'+ (m<=9?'0'+m:m) +'-'+ (d<=9?'0'+d:d) + '  ' + date.toLocaleTimeString();
}

// trend_controller
  
dbutil.trend_controller = function(){
    try{

        this.items = [];
        this.range={};
        this.datarange={};
        this.base={}; 
        this.selectedid = {};
        this.pugerange= function(){
            var tmp={};
            for(var key in this.range) {
                if (this.range[key])
                    tmp[key]=this.range[key];
                    
            }
            this.range=tmp;
            var datatmp={};
            for(var key in this.datarange) {
                if (this.datarange[key])
                    datatmp[key]=this.datarange[key];
                    
            }
            this.datarange=datatmp;
        }
        this.xmllist = dbutil.database.getXMLData(this, 'TrendList');
        this.connect();
    }
    catch(error){      
        dbutil.database.modal(dbutil.database.FATAL, error);
    }  
};


dbutil.trend_controller.MAX_PERIOD = 360000000;

dbutil.trend_controller.MIN_PERIOD = 60000;

dbutil.trend_controller.MID_PERIOD = 10800000;

dbutil.trend_controller.COLORS = [
    '4572A7', 
    'AA4643', 
    '89A54E', 
    '80699B', 
    '3D96AE', 
    'DB843D', 
    '92A8CD', 
    'A47D7C', 
    'B5CA92'
    ];


dbutil.trend_controller.prototype.connect = function(noinit){
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
            this.updateselect();
            this.updatelist();
            this.setselectpanel(false);}
        //this.setStart(new Date('Sep 10 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        this.setStart(new Date((new Date()).valueOf() - dbutil.trend_controller.MID_PERIOD));
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


dbutil.trend_controller.prototype.attach = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    window.trendcontroller = this;
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





dbutil.trend_controller.prototype.parseXMLData = function(){
    this.xml=[];
    var j=0;
    for(var e=this.xmllist.firstElementChild; e; e=e.nextElementSibling){
        var lst= e.getAttribute("name");                       
        for(var el=e.firstElementChild; el; el=el.nextElementSibling){
            var arr= el.getAttribute("name"); 
            for(var et=el.firstElementChild; et; et=et.nextElementSibling){                               
                var tg = et.getAttribute("tg");
                if (this.base[tg])
                    this.xml.push({
                        list: lst, 
                        array: arr, 
                        tag: tg,
                        comment: this.base[tg].comment,
                        eu: this.base[tg].eu,
                        mineu: this.base[tg].mineu,
                        maxeu: this.base[tg].maxeu,
                        rowid: (++j).toString()
                    })                         
            }                                                        
        }
    }   
}



dbutil.trend_controller.prototype.inittags = function(val){
    this.base = {};
    for (var i=0;i<val.length;++i){
        this.base[val[i].name] = val[i];
    }
}


dbutil.trend_controller.prototype.init = function(){
    
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
        window.trendcontroller.run();
    ;
    })

    $( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.trendcontroller.resetselectpanel();
    ;
    });
    
    $( "#noparam-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-0"
        }
    }).click(function() {
        window.trendcontroller.removeall();
    ;
    });    
    
    
    $( "#left-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-w"
        }
    }).click(function() {
        window.trendcontroller.setLeft();
    });
    
    $( "#right-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.trendcontroller.setRight();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.trendcontroller.setNow();
    ;
    });  
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.trendcontroller.setNow();
    ;
    });     


    $("#select-panel-trend" ).position({
        of: $( "#top-menuemain" ),
        my: 'left bottom',
        at: 'left top'
    });    
    
    this.setselectpanel(false);
    
    var panelheight = $("#select-panel-trend" )[0].getClientRects ? $("#select-panel-trend" )[0].getClientRects()[0].height : undefined;
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
        colNames:['list','array', 'Тег', 'Наименование', 'Ед. изм.', 'min', 'max'],     
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
            name:'array',
            index:'array', 
            width:1, 
            hidden: true
        },

        {
            name:'tag',
            index:'tag'
        },
        
        {
            name:'comment',
            index:'comment',
            width: 600
        },
        
        {
            name:'eu',
            index:'eu'
        },   
            
        
        {
            name:'mineu',
            index:'mineu'
        },
        
        {
            name:'maxeu',
            index:'maxeu'
        },        
    
		
        ],
        rowNum: 100000,
        //treeIcons: {plus:'ui-icon-circle-arrow-e',minus:'ui-icon-triangle-1-s',leaf:'ui-icon-radio-off'},
   	hidegrid: false,
        viewrecords: true,
        multiselect: true,
        grouping:true,
        groupingView : {
            groupField : ['list','array'],
            groupSummary : [false],
            groupColumnShow : [false],
            groupText : ['<b>{0}</b>'],
            groupCollapse : true,
            groupOrder: ['asc'],
            groupCollapse: true
        },
        
        caption: 'Выбор параметра'
   	
    });
    

    
    
    $("#selectlist").jqGrid({
        data: this.items,
        autowidth: true,
        datatype: "local",
        height: bottomheight ? bottomheight : 'auto',
        scrollrows: true,
        shrinkToFit: false,
        cellLayout: 1,
        colNames:['Тэг', 'Наименование', 'Ед. изм.', 'Диапозон' ,'Диапозон данных' ,'Выбранный диапозон' , 'Авто', 'Выбор' ,'Цвет' , ' ', 'color', 'auto', 'min', 'max', 'mineu', 'maxeu'],
        colModel:[
                    
        {
            name:'id',
            index:'id'
        },
        
        {
            name:'comment',
            index:'comment',
            width: 600
        },
        
        {
            name:'eu',
            index:'eu'
        },  
        {
            name:'range',
            index:'range'
        },  
        {
            name:'datarange',
            index:'datarange'
        },    
        {
            name:'selectrange',
            index:'selectrange'
        },          
        {
            name:'autoedit',
            index:'autoedit',
            width:30
        },
        {
            name:'rangeedit',
            index:'rengeedit',
            width:260
        },        
        {
            name:'coloredit',
            index:'coloredit'

        }, 
  
        {
            name: 'oprt', 
            width:35, 
            fixed:true
        },

        {
            name:'color',
            index:'color',
            width: 1

        },  
        {
            name:'auto',
            index:'auto',
            width: 1

        },  
        {
            name:'min',
            index:'min',
            width: 1

        },          
        {
            name:'max',
            index:'max',
            width: 1

        },  	
        {
            name:'mineu',
            index:'mineu',
            width: 1            
        },
        
        {
            name:'maxeu',
            index:'maxeu',
            width: 1            
        }	
        ],
   	
        viewrecords: false,
        onSelectRow: function (rowId, status, e) {
            var row = $("#selectlist").jqGrid('getRowData',rowId);
            ts.setselect(row.id, status);         
        },  

        gridComplete: function(){ 
            var ids = $("#selectlist").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
               
                var row = $("#selectlist").jqGrid('getRowData',ids[i]);
                var colid = 'selectlist_selectcolor_'+ids[i];
                var rangeid = 'selectlist_selectrange_'+ids[i];
                var delid = 'selectlist_selectremove_'+ids[i];
                var autostate= row.auto=="true" ? 'checked="true"' : '';
               
                var col =   "<input  class='color-selector-ui' style='background-color:#"+ row.color + "' type='text'  value='"+ row.color + "'  id='"+colid+"'/>";
                var aut =   "<input  style='' type='checkbox' " + autostate + "  onchange=\"window.trendcontroller.setauto('"+row.id+"',this.checked)\"/>";
                var range = "<div id='"+rangeid+"' style='padding-left: 10px, padding-right: 10px; width: 100%;'/>";
                var del =   "<button id='"+delid+"' style='height: 18px' onclick=\"window.trendcontroller.remove('"+row.id+"')\">Удалить</button>";
               
                $("#selectlist").jqGrid('setCell',ids[i] ,'coloredit' ,col);
                $("#selectlist").jqGrid('setCell',ids[i] ,'autoedit' ,aut);
                $("#selectlist").jqGrid('setCell',ids[i] ,'oprt' ,del);
   
               
                $('#'+colid)[0].nameid=row.id;              
                $('#'+colid).colorpicker({
                    close: function(ev,col){
                        ev.target.setAttribute('style','background-color:#'+col.formatted);
                        ts.setcolor(ev.target.nameid, col.formatted);
                    },
                    select: function(ev,col){
                        ev.target.setAttribute('style','background-color:#'+col.formatted);
                    }                   
                });                             
                if (row.auto!="true"){
                    $("#selectlist").jqGrid('setCell',ids[i] ,'rangeedit' ,range);
                    $('#'+rangeid)[0].nameid=row.id;
                    $('#'+rangeid).slider({
                        range: true,
                        min: parseFloat(row.mineu),
                        max: parseFloat(row.maxeu),
                        values: window.trendcontroller.range[row.id] ? [ window.trendcontroller.range[row.id].min , window.trendcontroller.range[row.id].max ] : [ row.min.valueOf(), row.max.valueOf() ],
                        change: function(ev, ui) {
                            window.trendcontroller.setextremes(ev.target.nameid, ui.values[ 0 ],ui.values[ 1 ])
                        }
                    });
                }           
                $('#'+delid).button({
                    text: false,
                    icons: {
                        primary: "ui-icon-circle-minus"
                    }
                });
            }
        }         
        	
    });                               
}; 



   


dbutil.trend_controller.prototype.add = function(tag){
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


dbutil.trend_controller.prototype.remove= function(id, exclude){
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
    if(this.trendchart)
        this.trendchart.removeseries(id);
    this.updateselect();
    this.pugerange();
    return true;      
}

dbutil.trend_controller.prototype.removeall= function(){
    //for (var j=0;j<this.items.length;++j){
    $("#list").jqGrid('resetSelection');
 
    this.items = [];
    this.range = {};
    this.datarange = {}; 
    if (this.trendchart)
        this.trendchart.detach();
    this.trendchart=undefined;
    this.updateselect();
    this.pugerange();        
}

dbutil.trend_controller.prototype.selectcolor = function(){
    var result = 'FF0000';
    var j=0;
    while (j<dbutil.trend_controller.COLORS.length){
        var fnd = false;
        for (var i=0;i<this.items.length;++i){
            if (this.items[i].color==dbutil.trend_controller.COLORS[j])
                fnd = true;
        }
        if (!fnd) return dbutil.trend_controller.COLORS[j];
        j++;
    }
    return result;
}


dbutil.trend_controller.prototype.updatedataextremes = function(){
    for (var i=0;i<this.items.length;++i){
        var id = this.items[i].id;
        var ext=this.trendchart ? this.trendchart.getExtremes(id) : null;
        this.datarange[id] = ext ? {
            min : ext.dataMin,
            max : ext.dataMax
        } : undefined;
                   
        this.items[i].datarange= ext && (ext.dataMax || ext.dataMax===0) && (ext.dataMin || ext.dataMin===0) ? 
        (ext.dataMin.toFixed(2)  + ' - ' + ext.dataMax.toFixed(2)) : '';                                         
    }  
    this.updateselect(); 
}

dbutil.trend_controller.prototype.updateselect = function( req ) {
    $("#selectlist").jqGrid('clearGridData');
    for (var i=0;i<this.items.length;++i)
        this.items[i].rowid=(i+1).toString();
    //    $("#selectlist").jqGrid('addRowData',(i+1).toString(),this.items[i]);    
    $("#selectlist").jqGrid('addRowData','rowid',this.items); 
    this.requested=req;
    this.setstate();
}

dbutil.trend_controller.prototype.updatelist = function( req ) {
    $("#list").jqGrid('clearGridData');
    //for (var i=0;i<this.xml.length;++i)
    //    this.xml[i].rowid=(i+1).toString();
    //    $("#list").jqGrid('addRowData',(i+1).toString(),this.xml[i]); 
        $("#list").jqGrid('addRowData',"rowid",this.xml);   
        $("#list").trigger("reloadGrid");
}


    
dbutil.trend_controller.prototype.tags = function(){
    var rslt = [];
    for (var i=0;i<this.items.length;++i)
        rslt.push(this.items[i].id);   
    return rslt;
}  

dbutil.trend_controller.prototype.colors = function(){
    var rslt = [];
    for (var i=0;i<this.items.length;++i)
        rslt.push('#'+this.items[i].color);   
    return rslt;
} 

dbutil.trend_controller.prototype.run = function(){
    this.setselectpanel(false);
    dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_DATAREQUEST );
    if (this.trendchart)
        this.trendchart.detach();
    this.trendchart=undefined;
    var ts = this;
    ts.requested=true;
    ts.setstate();
    this.trendchart = new libutil.trendchart( 
    {
        connection: this.connection , 
        tags: this.tags(), 
        element: "chart-id", 
        colors: this.colors(),  
        start: this.start , 
        stop: this.stop, 
        ranges: this.range,
        callback: function(ev){
            if (ev.error) {
                  dbutil.database.reportError(ev, ts, true);
                  return;
            }
            else{
            $('#runmodal').dialog('close');
            ts.requested=true;
            ts.setstate();}
        },
        complete: function(){
            ts.updatedataextremes();
        }
    });
        
}


dbutil.trend_controller.prototype.setStart = function(val){
    dbutil.database.setStart(val, this, dbutil.trend_controller.MIN_PERIOD, dbutil.trend_controller.MAX_PERIOD);
}

dbutil.trend_controller.prototype.setStop = function(val){
    dbutil.database.setStop(val, this, dbutil.trend_controller.MIN_PERIOD, dbutil.trend_controller.MID_PERIOD , dbutil.trend_controller.MAX_PERIOD);
}

dbutil.trend_controller.prototype.setLeft = function(){
    dbutil.database.setLeft(this);
}

dbutil.trend_controller.prototype.setRight = function(){
    dbutil.database.setRight(this);
}

dbutil.trend_controller.prototype.setNow = function(){
    dbutil.database.setNow(this);
}

dbutil.trend_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

dbutil.trend_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}

dbutil.trend_controller.prototype.setcolor = function(id, col){
    
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if(this.trendchart)
                this.trendchart.setcolor(id,'#'+col);
            this.items[i].color=col;
            this.requested=false;
            this.setstate();
            break;
        } 
    }
}
dbutil.trend_controller.prototype.setselect = function(id, state){
       if(this.trendchart)
            this.trendchart.setSelect(id, state);
}

dbutil.trend_controller.prototype.setauto = function(id, val){
    
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if (this.items[i].auto!=val){
                if (!val){
                    var ext=this.trendchart ? this.trendchart.getExtremes(id) : null;
                    this.range[id] = {
                        min : (ext ? ext.min : this.items[i].mineu),
                        max : (ext ? ext.max : this.items[i].maxeu)
                    };
                    this.items[i].selectrange= ext ? (this.range[id].min + ' - ' + this.range[id].max) : '';
                }          
                else{
                    this.range[id] = undefined; 
                    this.items[i].selectrange= '';
                    if (this.trendchart) 
                        this.trendchart.setExtremesAuto(id);
                }           
                this.items[i].auto=val;
                this.updateselect();
                this.pugerange();
                break;
            }
        } 
    }
}

dbutil.trend_controller.prototype.setextremes = function(id, min, max){
    for (var i=0;i<this.items.length;++i){
        if (this.items[i].id==id){
            if(this.trendchart){
                this.trendchart.setExtremes(id, min, max);
                this.range[id] = {
                    min : min,
                    max : max
                };
                this.items[i].selectrange=(min + ' - ' + max); 
                this.updateselect();
            }   
        }
    }
}



dbutil.trend_controller.prototype.setselectpanel = function(val){
    var panel = $( "#select-panel-trend" )[0];
    panel.className = val ? 'ui-widget-content select-panel-visible' : 'ui-widget-content select-panel-hidden';
    panel.visibility = val ? true : false;   
}

dbutil.trend_controller.prototype.resetselectpanel = function(){
    var panel = $( "#select-panel-trend" )[0];
    this.setselectpanel(!panel.visibility);    
}


dbutil.trend_controller.prototype.setstate = function(){
    $( "#run-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#left-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#right-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");    
    $( "#select-button" ).button((this.xml.length) ? "enable"  : "disable");
    $( "#noparam-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#print-button" ).button((this.trendchart) ? "enable"  : "disable");
    if (!this.items.length && this.xml.length)
        this.setselectpanel(true);
}


// journal_controller


  
dbutil.journal_controller = function(){
    try{
        //var tst = dbutil.journal_controller.getClass(0,3);
        this.journal = [];
        this.checked = dbutil.journal_controller.MSG_FULL;
        this.datarange={};
        this.base={};        
        this.xmllist = dbutil.database.getXMLData(this, 'meta');
        this.connect();
    }
    catch(error){      
        dbutil.database.modal(dbutil.database.FATAL, error);
    }  
};


dbutil.journal_controller.MAX_PERIOD = 2678400000;

dbutil.journal_controller.MIN_PERIOD = 60000;

dbutil.journal_controller.HOUR_PERIOD = 3600000;

dbutil.journal_controller.DAY_PERIOD = 86400000;

dbutil.journal_controller.MSG_FULL = 8191;

dbutil.journal_controller.MSG_NAME_ACCIDEND_NEW = "Авария новая";
dbutil.journal_controller.MSG_NAME_ACCIDEND_KVIT = "Авария квитированная";
dbutil.journal_controller.MSG_NAME_ACCIDEND_OUT = "Авария ушедшая";
dbutil.journal_controller.MSG_NAME_ALARM_NEW = "Тревога новая";
dbutil.journal_controller.MSG_NAME_ALARM_KVIT = "Тревога квитированная";
dbutil.journal_controller.MSG_NAME_ALARM_OUT = "Тревога ушедшая";
dbutil.journal_controller.MSG_NAME_WARNING_NEW = "Уведомление новое";
dbutil.journal_controller.MSG_NAME_WARNING_KVIT = "Уведомление квитированное";
dbutil.journal_controller.MSG_NAME_WARNING_OUT = "Уведомление ушедшее";
dbutil.journal_controller.MSG_NAME_ON = "Включение";
dbutil.journal_controller.MSG_NAME_OFF = "Выключение";
dbutil.journal_controller.MSG_NAME_COMMAND = "Команда";
dbutil.journal_controller.MSG_NAME_EVENT = "Событие";

dbutil.journal_controller.MSG_CLASS_ACCIDEND_NEW = "message-accedent-new";
dbutil.journal_controller.MSG_CLASS_ACCIDEND_KVIT = "message-accedent-kvit";
dbutil.journal_controller.MSG_CLASS_ACCIDEND_OUT = "message-accedent-out";
dbutil.journal_controller.MSG_CLASS_ALARM_NEW = "message-alarm-new";
dbutil.journal_controller.MSG_CLASS_ALARM_KVIT = "message-alarm-kvit";
dbutil.journal_controller.MSG_CLASS_ALARM_OUT = "message-alarm-out";
dbutil.journal_controller.MSG_CLASS_WARNING_NEW = "message-warning-new";
dbutil.journal_controller.MSG_CLASS_WARNING_KVIT = "message-warning-kvit";
dbutil.journal_controller.MSG_CLASS_WARNING_OUT = "message-warning-out";
dbutil.journal_controller.MSG_CLASS_ON = "message-message-on";
dbutil.journal_controller.MSG_CLASS_OFF = "message-message-off";
dbutil.journal_controller.MSG_CLASS_COMMAND = "message-message-command";
dbutil.journal_controller.MSG_CLASS_EVENT = "message-message-event";

   /* const msgtype msNew        = 0x00;
    const msgtype msKvit       = 0x01;
    const msgtype msOut        = 0x02;
    const msgtype msOn         = 0x03;
    const msgtype msOff        = 0x04;
    const msgtype msCmd        = 0x05;
    const msgtype msTimeEvent  = 0x06;
    const msgtype msTimeAlarm  = 0x07;*/

dbutil.journal_controller.MESSAGE_TYPE =[
    {rowid: "1", css: dbutil.journal_controller.MSG_CLASS_ACCIDEND_NEW,    name: dbutil.journal_controller.MSG_NAME_ACCIDEND_NEW, level: 3, type: 0},
    {rowid: "2", css: dbutil.journal_controller.MSG_CLASS_ACCIDEND_KVIT,   name: dbutil.journal_controller.MSG_NAME_ACCIDEND_KVIT, level: 3, type: 1}, 
    {rowid: "3", css: dbutil.journal_controller.MSG_CLASS_ACCIDEND_OUT,    name: dbutil.journal_controller.MSG_NAME_ACCIDEND_OUT, level: 3, type: 2}, 
    {rowid: "4", css: dbutil.journal_controller.MSG_CLASS_ALARM_NEW,       name: dbutil.journal_controller.MSG_NAME_ALARM_NEW, level: 2, type: 0},
    {rowid: "5", css: dbutil.journal_controller.MSG_CLASS_ALARM_KVIT,      name: dbutil.journal_controller.MSG_NAME_ALARM_KVIT, level: 2, type: 1}, 
    {rowid: "6", css: dbutil.journal_controller.MSG_CLASS_ALARM_OUT,       name: dbutil.journal_controller.MSG_NAME_ALARM_OUT, level: 2, type: 2},
    {rowid: "7", css: dbutil.journal_controller.MSG_CLASS_WARNING_NEW,     name: dbutil.journal_controller.MSG_NAME_WARNING_NEW, level: 1, type: 0},
    {rowid: "8", css: dbutil.journal_controller.MSG_CLASS_WARNING_KVIT,    name: dbutil.journal_controller.MSG_NAME_WARNING_KVIT, level: 1, type: 1}, 
    {rowid: "9", css: dbutil.journal_controller.MSG_CLASS_WARNING_OUT,     name: dbutil.journal_controller.MSG_NAME_WARNING_OUT, level: 1, type: 2},
    {rowid: "10", css: dbutil.journal_controller.MSG_CLASS_ON ,            name: dbutil.journal_controller.MSG_NAME_ON, level: 0, type: 3},
    {rowid: "11", css: dbutil.journal_controller.MSG_CLASS_OFF,            name: dbutil.journal_controller.MSG_NAME_OFF, level: 0, type: 4},
    {rowid: "12", css: dbutil.journal_controller.MSG_CLASS_COMMAND,        name: dbutil.journal_controller.MSG_NAME_COMMAND, level: 0, type: 5}, 
    {rowid: "13", css: dbutil.journal_controller.MSG_CLASS_EVENT,          name: dbutil.journal_controller.MSG_NAME_EVENT, level: 0, type: 6}  
];


dbutil.journal_controller.getClass = function(type,level){
   if (!dbutil.journal_controller.CLASS_MAP){
       dbutil.journal_controller.CLASS_MAP = {};
       for (var i=0;i<dbutil.journal_controller.MESSAGE_TYPE.length;++i){
           if (!dbutil.journal_controller.CLASS_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()]){
               dbutil.journal_controller.CLASS_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()]={};}
           dbutil.journal_controller.CLASS_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()][dbutil.journal_controller.MESSAGE_TYPE[i].level.toString()]=
               dbutil.journal_controller.MESSAGE_TYPE[i].css;
       }
   }
   var tp = dbutil.journal_controller.CLASS_MAP[type.toString()];
   if (!tp) return "";
   return tp[level.toString()] ? tp[level.toString()] : "";
}

dbutil.journal_controller.getTitle = function(type,level){
   if (!dbutil.journal_controller.TITLE_MAP){
       dbutil.journal_controller.TITLE_MAP = {};
       for (var i=0;i<dbutil.journal_controller.MESSAGE_TYPE.length;++i){
           if (!dbutil.journal_controller.TITLE_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()]){
               dbutil.journal_controller.TITLE_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()]={};}
           dbutil.journal_controller.TITLE_MAP[dbutil.journal_controller.MESSAGE_TYPE[i].type.toString()][dbutil.journal_controller.MESSAGE_TYPE[i].level.toString()]=
               dbutil.journal_controller.MESSAGE_TYPE[i].css;
       }
   }
   var tt = dbutil.journal_controller.TITLE_MAP[type.toString()];
   if (!tt) return "";
   return tt[level.toString()] ? tt[level.toString()] : "";
}


dbutil.journal_controller.prototype.connect = function(){
    try{
        var ts = this;
        this.xml= [];
        this.journal= [];
        this.init();
        this.setStart(new Date('Sep 01 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        //this.setStart(new Date((new Date()).valueOf() - dbutil.journal_controller.DAY_PERIOD));
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

dbutil.journal_controller.prototype.init = function(){
    
 
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
        window.journalcontroller.run();
    ;
    })

    $( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.journalcontroller.resetselectpanel();
    ;
    });
    
    
    $( "#day-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowstop-1-e"
        }
    }).click(function() {
        window.journalcontroller.setLastDay();
    });
    
    $( "#hour-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.journalcontroller.setLastHour();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.journalcontroller.setNow();
    ;
    });  
    
    $( "#allmessage-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-3"
        }
    }).click(function() {
        window.journalcontroller.checkall();
    ;
    });    
    
    $( "#nomessage-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-0"
        }
    }).click(function() {
        window.journalcontroller.checkno();
    ;
    });     
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.trendcontroller.setNow();
    ;
    });     

    this.startpicker = $('#starttime').datetimepicker({
        onClose:  function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStart(dt);
        }
    }).click(function(){});
    this.stoppicker = $('#stoptime').datetimepicker({
        onClose: function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStop(dt);
        }
    }).click(function(){});
    
    $("#select-panel-journal" ).position({
        of: $( "#top-menuemain" ),
        my: 'left bottom',
        at: 'left top'
    });  
    
    this.setselectpanel(false);
    
    var tableheight = $("#inner" )[0].getClientRects ? $("#inner" )[0].getClientRects()[0].height : undefined;
    
    
    this.tabgrid = $("#table-id").jqGrid({
        data: this.journal,
        autowidth: true,
        datatype: "local",
        height: tableheight ? tableheight : 'auto',
        scrollrows: true,
        shrinkToFit: true,
        sortable: false,

        colNames:[' ', 'Тег', 'Время', 'Сообщение', 'Группа','Значение','User', 'level', 'Type'],
        gridComplete: function(){ 
            var ids = $("#table-id").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
                var imgid = 'table_id_img_'+ids[i];
                var col =   "<span   class='message-message-icon' id='"+imgid+"'></span>";
                var row = $("#table-id").jqGrid('getRowData',ids[i]);
                $("#table-id").jqGrid('setCell',ids[i] ,'icon' ,col);
                $("#table-id").jqGrid('setRowData',ids[i],undefined,window.journalcontroller ? dbutil.journal_controller.getClass (parseInt(row.type), parseInt(row.level)): undefined);
                
            }
        },
        colModel:[  
        {
            name:'icon',
            index:'icon',
            title: false,
            width: 20,
            sortable: false
        },                    
        {
            name:'tag',
            index:'tag',
            title: false,
            sortable: false
        },
        {
            name:'time',
            index:'time',
            width: 150,
            title: false
            
        },

        {
            name:'text',
            index:'text',
            width: 600,
            title: false,
            sortable: false
        },
        {
            name:'agroup',
            index:'agroup',
            width: 100,
            title: false,
            sortable: false
        },        
        
        {
            name:'value',
            index:'value',
            title: false
            
        },
        
        {
            name:'user',
            index:'user',
            title: false,
            sortable: false
            
        },   
        {
            name:'level',
            index:'level',
            title: false,
            width: 1
        },  
    
        {
            name:'type',
            index:'type',
            title: false,
            width: 1
        },        
    
		
        ],
   	rowNum: 100000,
        viewrecords: true,
        sortable: true,
        sortname: 'time',
        sortorder: 'desc'
   	
    });
    
     this.checkgrid = $("#check-list").jqGrid({
        data: [],
        autowidth: true,
        datatype: "local",
        height: 350,
        scrollrows: true,
        shrinkToFit: true,
        sortable: false,

        colNames:[' ', 'Тип', ' ', '', ''],
        gridComplete: function(){ 
            var ids = $("#check-list").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
                var imgid = 'checklist_id_img_'+ids[i];          
                var row = $("#check-list").jqGrid('getRowData',ids[i]);
                var col =   "<span   class='message-message-icon' id='"+imgid+"'></span>";
                var cheched=window.journalcontroller.getcheck(ids[i]) ? 'checked="true"' : '';
                var check =   "<input  style='' type='checkbox' " + cheched + "  onchange=\"window.journalcontroller.setcheck('"+ids[i]+"',this.checked)\"/>";
                $("#check-list").jqGrid('setCell',ids[i] ,'icon' ,col);
                $("#check-list").jqGrid('setCell',ids[i] ,'check' ,check)
                $("#check-list").jqGrid('setRowData',ids[i],undefined,window.journalcontroller ? dbutil.journal_controller.getClass (parseInt(row.type), parseInt(row.level)): undefined);
                
            }
        },
        colModel:[  
        {
            name:'icon',
            index:'icon',
            title: false,
            width: 20,
            sortable: false
        },                    
        {
            name:'name',
            index:'name',
            title: false,      
            width: 250,
            sortable: false
        },
        {
            name:'check',
            index:'check',
            width: 30,
            title: false,
            sortable: false
        },  
        {
            name:'level',
            index:'level',
            title: false,
            width: 1
        },  
    
        {
            name:'type',
            index:'type',
            title: false,
            width: 1
        },        
    
		
        ],
   	rowNum: 100000,
        viewrecords: true,
        sortable: true,
        sortname: 'time',
        sortorder: 'desc'
   	
    });
    
    


}

dbutil.journal_controller.prototype.attach = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    window.journalcontroller = this;
    this.selecttable()
    this.connection = ev.connection;
    this.requested=false;
    this.setstate(); 
    dbutil.database.clearmodal();
    
}


dbutil.journal_controller.prototype.run = function(){
    var ts=this;
    this.setselectpanel(false);
    dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_DATAREQUEST);
    this.connection.select_journal ( function(){var evnt=event;window.journalcontroller.dataresponse(evnt);}, this.start , this.stop, this.filter());
}

dbutil.journal_controller.prototype.dataresponse = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    this.journal = ev.table;
    dbutil.database.clearmodal();
    this.filltable();
}



dbutil.journal_controller.prototype.filltable = function() {
    $("#table-id").jqGrid('clearGridData');
    for (var j=0;j<this.journal.length;++j){
        var i=j;//this.journal.length-1-j;
        this.journal[i].time= dbutil.database.date(this.journal[i].time);
        this.journal[i].icon= '';
        this.journal[i].rowid=(i+1).toString();} 
    $("#table-id").jqGrid('addRowData',"rowid" ,this.journal);
    $("#table-id").trigger("reloadGrid");
    this.requested=false;
    this.setstate();
}

dbutil.journal_controller.prototype.selecttable = function() {
    this.checkitem=[];
    for (var i=0;i<dbutil.journal_controller.MESSAGE_TYPE.length;++i){
        this.checkitem.push(
        {icon : '',
         check: '',
         rowid: dbutil.journal_controller.MESSAGE_TYPE[i].rowid,
         name: dbutil.journal_controller.MESSAGE_TYPE[i].name,
         level: dbutil.journal_controller.MESSAGE_TYPE[i].level,
         type: dbutil.journal_controller.MESSAGE_TYPE[i].type
    })};
    $("#check-list").jqGrid('clearGridData');
    $("#check-list").jqGrid('addRowData',"rowid" ,this.checkitem);
    $("#check-list").trigger("reloadGrid");
}

dbutil.journal_controller.prototype.setcheck = function(rowid, state){
var bitnum=parseInt(rowid);
if (!bitnum) return false;
if (state)
    this.checked = this.checked | (1 << (bitnum-1));
else
    this.checked = this.checked & (~(1 << (bitnum-1)));
this.setstate();
$("#check-list").trigger("reloadGrid");}

dbutil.journal_controller.prototype.getcheck = function(rowid){
    var bitnum=parseInt(rowid);
    if (!bitnum) return false;
    return (this.checked & (1 << (bitnum-1))) ? true : false;}

dbutil.journal_controller.prototype.checkall = function(rowid){
this.checked = dbutil.journal_controller.MSG_FULL;
this.setstate();
$("#check-list").trigger("reloadGrid");}

dbutil.journal_controller.prototype.checkno = function(rowid){
this.checked = 0;
this.setstate();
$("#check-list").trigger("reloadGrid");}


dbutil.journal_controller.prototype.filter = function(){
  if (this.checked==dbutil.journal_controller.MSG_FULL)
    return undefined;
  var rslt=""
  for (var i=0;i<dbutil.journal_controller.MESSAGE_TYPE.length;++i){
      if (this.checked & (1 << (i))){
          rslt+= rslt=="" ? " ( " : " or ";
          rslt+= "( itype=" + dbutil.journal_controller.MESSAGE_TYPE[i].type + " and ilevel=" + dbutil.journal_controller.MESSAGE_TYPE[i].level+ " )";}}
  rslt+= rslt=="" ? " " : " )";
  //console.log('rslt', rslt);    
  return rslt;
}

dbutil.journal_controller.prototype.setStart = function(val){
    dbutil.database.setStart(val, this, dbutil.journal_controller.MIN_PERIOD, dbutil.journal_controller.MAX_PERIOD);
}

dbutil.journal_controller.prototype.setStop = function(val){
    dbutil.database.setStop(val, this, dbutil.trend_controller.MIN_PERIOD, dbutil.journal_controller.DAY_PERIOD ,dbutil.trend_controller.MAX_PERIOD);
}


dbutil.journal_controller.prototype.setLastHour = function(){
    dbutil.database.setNow(this, dbutil.journal_controller.HOUR_PERIOD);;
    this.run();
}

dbutil.journal_controller.prototype.setLastDay = function(){
    dbutil.database.setNow(this, dbutil.journal_controller.DAY_PERIOD);;
    this.run();
}

dbutil.journal_controller.prototype.setNow = function(){
    dbutil.database.setNow(this);
    this.run();
}

dbutil.journal_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

dbutil.journal_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}

dbutil.journal_controller.prototype.setstate = function(){
    $( "#select-button" ).button((this.connection && this.checkitem && this.checkitem.length) ? "enable"  : "disable");
    $( "#allmessage-button" ).button((this.connection && this.checkitem && this.checkitem.length && this.checked != dbutil.journal_controller.MSG_FULL) ? "enable"  : "disable");
    $( "#nomessage-button" ).button((this.connection && this.checkitem && this.checkitem.length && this.checked) ? "enable"  : "disable");
    $( "#run-button" ).button((!this.requested && this.connection && this.checked) ? "enable"  : "disable");
    $( "#hour-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#day-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");} 

dbutil.journal_controller.prototype.setselectpanel = function(val){
    var panel = $( "#select-panel-journal" )[0];
    panel.className = val ? 'ui-widget-content select-panel-visible' : 'ui-widget-content select-panel-hidden';
    panel.visibility = val ? true : false;   
}

dbutil.journal_controller.prototype.resetselectpanel = function(){
    var panel = $( "#select-panel-journal" )[0];
    this.setselectpanel(!panel.visibility);    
}




// debug_controller


  
dbutil.debug_controller = function(){
    try{
        //var tst = dbutil.debug_controller.getClass(0,3);
        this.debug = [];
        this.checked = dbutil.debug_controller.MSG_FULL;
        this.base={};        
        this.xmllist = dbutil.database.getXMLData(this, 'meta');
        this.connect();
    }
    catch(error){      
        dbutil.database.modal(dbutil.database.FATAL, error);
    }  
};


dbutil.debug_controller.MAX_PERIOD = 2678400000;

dbutil.debug_controller.MIN_PERIOD = 60000;

dbutil.debug_controller.HOUR_PERIOD = 3600000;

dbutil.debug_controller.DAY_PERIOD = 86400000;

dbutil.debug_controller.MSG_FULL = 15;

dbutil.debug_controller.MSG_NAME_ACCIDEND = "Фатальная ошибка";
dbutil.debug_controller.MSG_NAME_ERROR = "Ошибка";
dbutil.debug_controller.MSG_NAME_WARNING = "Предупреждение";
dbutil.debug_controller.MSG_NAME_MESSAGE = "Уведомление";

dbutil.debug_controller.MSG_CLASS_ACCIDEND = "message-fatal-new";
dbutil.debug_controller.MSG_CLASS_ERROR = "message-accedent-new";
dbutil.debug_controller.MSG_CLASS_WARNING = "message-alarm-new";
dbutil.debug_controller.MSG_CLASS_MESSAGE = "message-warning-new";

  /*const debuglvtype DEBUG_FATALERROR = 0;
    const debuglvtype DEBUG_ERROR      = 1;
    const debuglvtype DEBUG_WARNING    = 2;
    const debuglvtype DEBUG_MESSAGE    = 3;*/

dbutil.debug_controller.MESSAGE_TYPE =[
    {rowid: "1", css: dbutil.debug_controller.MSG_CLASS_ACCIDEND,    name: dbutil.debug_controller.MSG_NAME_ACCIDEND, level: 0},
    {rowid: "2", css: dbutil.debug_controller.MSG_CLASS_ERROR,   name: dbutil.debug_controller.MSG_NAME_ERROR, level: 1}, 
    {rowid: "3", css: dbutil.debug_controller.MSG_CLASS_WARNING,    name: dbutil.debug_controller.MSG_NAME_WARNING, level: 2}, 
    {rowid: "4", css: dbutil.debug_controller.MSG_CLASS_MESSAGE,       name: dbutil.debug_controller.MSG_NAME_MESSAGE, level: 3} 
];


dbutil.debug_controller.getClass = function(level){
   if (!dbutil.debug_controller.CLASS_MAP){
       dbutil.debug_controller.CLASS_MAP = {};
       for (var i=0;i<dbutil.debug_controller.MESSAGE_TYPE.length;++i)
           dbutil.debug_controller.CLASS_MAP[dbutil.debug_controller.MESSAGE_TYPE[i].level.toString()]=dbutil.debug_controller.MESSAGE_TYPE[i].css;
   }   
   var tp = dbutil.debug_controller.CLASS_MAP[level.toString()];
   return tp ? tp : "";
}

dbutil.debug_controller.getTitle = function(level){
   if (!dbutil.debug_controller.CLASS_TITLE){
       dbutil.debug_controller.CLASS_TITLE = {};
       for (var i=0;i<dbutil.debug_controller.MESSAGE_TYPE.length;++i)
           dbutil.debug_controller.CLASS_TITLE[dbutil.debug_controller.MESSAGE_TYPE[i].level.toString()]=dbutil.debug_controller.MESSAGE_TYPE[i].css;
   }   
   var tt = dbutil.debug_controller.CLASS_TITLE[level.toString()];
   return tt ? tt : "";
}


dbutil.debug_controller.prototype.connect = function(){
    try{
        var ts = this;
        this.xml= [];
        this.debug= [];
        this.init();
        this.setStart(new Date('Sep 01 2012 10:40:42'));
        //this.setStop(new Date('Sep 10 2012 15:40:42'));
        //this.setStart(new Date('Sep 04 2012 10:40:42'));
        //this.setStop(new Date('Sep 04 2012 12:40:42'));         
        //this.setStart(new Date((new Date()).valueOf() - dbutil.debug_controller.DAY_PERIOD));
        this.setStop(/*new Date()*/new Date('Sep 21 2012 10:40:42'));        
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

dbutil.debug_controller.prototype.init = function(){
    
 
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
        window.debugcontroller.run();
    ;
    })

    $( "#select-button" ).button({
        text: false,
        disabled: true,       
        icons: {
            primary: "ui-icon-suitcase"
        }
    }).click(function() {
        window.debugcontroller.resetselectpanel();
    ;
    });
    
    
    $( "#day-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowstop-1-e"
        }
    }).click(function() {
        window.debugcontroller.setLastDay();
    });
    
    $( "#hour-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrow-1-e"
        }
    }).click(function() {
        window.debugcontroller.setLastHour();
    ;
    });   
    
    $( "#now-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-arrowthickstop-1-e"
        }
    }).click(function() {
        window.debugcontroller.setNow();
    ;
    });  
    
    $( "#allmessage-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-3"
        }
    }).click(function() {
        window.debugcontroller.checkall();
    ;
    });    
    
    $( "#nomessage-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-battery-0"
        }
    }).click(function() {
        window.debugcontroller.checkno();
    ;
    });     
    
    $( "#print-button" ).button({
        text: false,
        disabled: true,        
        icons: {
            primary: "ui-icon-print"
        }
    }).click(function() {
        //window.trendcontroller.setNow();
    ;
    });     

    this.startpicker = $('#starttime').datetimepicker({
        onClose:  function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStart(dt);
        }
    }).click(function(){});
    this.stoppicker = $('#stoptime').datetimepicker({
        onClose: function(){
            var dt = $(this).datetimepicker('getDate');
            ts.setStop(dt);
        }
    }).click(function(){});
    
    $("#select-panel-debug" ).position({
        of: $( "#top-menuemain" ),
        my: 'left bottom',
        at: 'left top'
    });  
    
    this.setselectpanel(false);
    
    var tableheight = $("#inner" )[0].getClientRects ? $("#inner" )[0].getClientRects()[0].height : undefined;
    
    
    this.tabgrid = $("#table-id").jqGrid({
        data: this.debug,
        autowidth: true,
        datatype: "local",
        height: tableheight ? tableheight : 'auto',
        scrollrows: true,
        shrinkToFit: true,
        sortable: false,

        colNames:[' ', 'Время', 'Текст','App', 'level'],
        gridComplete: function(){ 
            var ids = $("#table-id").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
                var imgid = 'table_id_img_'+ids[i];
                var col =   "<span   class='message-message-icon' id='"+imgid+"'></span>";
                var row = $("#table-id").jqGrid('getRowData',ids[i]);
                $("#table-id").jqGrid('setCell',ids[i] ,'icon' ,col);
                $("#table-id").jqGrid('setRowData',ids[i],undefined,window.debugcontroller ? dbutil.debug_controller.getClass (parseInt(row.level)): undefined);
                
            }
        },
        colModel:[  
        {
            name:'icon',
            index:'icon',
            title: false,
            width: 20,
            sortable: false
        },                    
        {
            name:'time',
            index:'time',
            width: 150,
            title: false
            
        },

        {
            name:'message',
            index:'message',
            width: 600,
            title: false,
            sortable: false
        },
        {
            name:'appid',
            index:'appid',
            width: 100,
            title: false,
            sortable: false
        },        
  
        {
            name:'level',
            index:'level',
            title: false,
            width: 1
        },  
    
       
    
		
        ],
   	rowNum: 100000,
        viewrecords: true,
        sortable: true,
        sortname: 'time',
        sortorder: 'desc'
   	
    });
    
     this.checkgrid = $("#check-list").jqGrid({
        data: [],
        autowidth: true,
        datatype: "local",
        height: 150,
        scrollrows: true,
        shrinkToFit: true,
        sortable: false,

        colNames:[' ', 'Тип', ' ', ''],
        gridComplete: function(){ 
            var ids = $("#check-list").jqGrid('getDataIDs');
            for(var i=0;i < ids.length;i++){
                var imgid = 'checklist_id_img_'+ids[i];          
                var row = $("#check-list").jqGrid('getRowData',ids[i]);
                var col =   "<span   class='message-message-icon' id='"+imgid+"'></span>";
                var cheched=window.debugcontroller.getcheck(ids[i]) ? 'checked="true"' : '';
                var check =   "<input  style='' type='checkbox' " + cheched + "  onchange=\"window.debugcontroller.setcheck('"+ids[i]+"',this.checked)\"/>";
                $("#check-list").jqGrid('setCell',ids[i] ,'icon' ,col);
                $("#check-list").jqGrid('setCell',ids[i] ,'check' ,check)
                $("#check-list").jqGrid('setRowData',ids[i],undefined,window.debugcontroller ? dbutil.debug_controller.getClass (parseInt(row.level)): undefined);
                
            }
        },
        colModel:[  
        {
            name:'icon',
            index:'icon',
            title: false,
            width: 20,
            sortable: false
        },                    
        {
            name:'name',
            index:'name',
            title: false,      
            width: 250,
            sortable: false
        },
        {
            name:'check',
            index:'check',
            width: 30,
            title: false,
            sortable: false
        },  
        {
            name:'level',
            index:'level',
            title: false,
            width: 1
        } 
           
    
		
        ],
   	rowNum: 100000,
        viewrecords: true,
        sortable: true,
        sortname: 'time',
        sortorder: 'desc'
   	
    });
    
    


}

dbutil.debug_controller.prototype.attach = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    window.debugcontroller = this;
    this.selecttable()
    this.connection = ev.connection;
    this.requested=false;
    this.setstate(); 
    dbutil.database.clearmodal();
    
}


dbutil.debug_controller.prototype.run = function(){
    var ts=this;
    this.setselectpanel(false);
    dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_DATAREQUEST);
    this.connection.select_debug ( function(){var evnt=event;window.debugcontroller.dataresponse(evnt);}, this.start , this.stop, this.filter());
}

dbutil.debug_controller.prototype.dataresponse = function(ev){
    if (ev.error){
        dbutil.database.reportError(ev, this);
        return;
    }
    this.debug = ev.table;
    dbutil.database.clearmodal();
    this.filltable();
}



dbutil.debug_controller.prototype.filltable = function() {
    $("#table-id").jqGrid('clearGridData');
    for (var j=0;j<this.debug.length;++j){
        var i=j;//this.debug.length-1-j;
        this.debug[i].time= dbutil.database.date(this.debug[i].time);
        this.debug[i].icon= '';
        this.debug[i].rowid=(i+1).toString();} 
    $("#table-id").jqGrid('addRowData',"rowid" ,this.debug);
    $("#table-id").trigger("reloadGrid");
    this.requested=false;
    this.setstate();
}

dbutil.debug_controller.prototype.selecttable = function() {
    this.checkitem=[];
    for (var i=0;i<dbutil.debug_controller.MESSAGE_TYPE.length;++i){
        this.checkitem.push(
        {icon : '',
         check: '',
         rowid: dbutil.debug_controller.MESSAGE_TYPE[i].rowid,
         name: dbutil.debug_controller.MESSAGE_TYPE[i].name,
         level: dbutil.debug_controller.MESSAGE_TYPE[i].level,
         type: dbutil.debug_controller.MESSAGE_TYPE[i].type
    })};
    $("#check-list").jqGrid('clearGridData');
    $("#check-list").jqGrid('addRowData',"rowid" ,this.checkitem);
    $("#check-list").trigger("reloadGrid");
}

dbutil.debug_controller.prototype.setcheck = function(rowid, state){
var bitnum=parseInt(rowid);
if (!bitnum) return false;
if (state)
    this.checked = this.checked | (1 << (bitnum-1));
else
    this.checked = this.checked & (~(1 << (bitnum-1)));
this.setstate();
$("#check-list").trigger("reloadGrid");}

dbutil.debug_controller.prototype.getcheck = function(rowid){
    var bitnum=parseInt(rowid);
    if (!bitnum) return false;
    return (this.checked & (1 << (bitnum-1))) ? true : false;}

dbutil.debug_controller.prototype.checkall = function(rowid){
this.checked = dbutil.debug_controller.MSG_FULL;
this.setstate();
$("#check-list").trigger("reloadGrid");}

dbutil.debug_controller.prototype.checkno = function(rowid){
this.checked = 0;
this.setstate();
$("#check-list").trigger("reloadGrid");}


dbutil.debug_controller.prototype.filter = function(){
  if (this.checked==dbutil.debug_controller.MSG_FULL)
    return undefined;
  var rslt=""
  for (var i=0;i<dbutil.debug_controller.MESSAGE_TYPE.length;++i){
      if (this.checked & (1 << (i))){
          rslt+= rslt=="" ? " ( " : " or ";
          rslt+= "(  \ilevel=" + dbutil.debug_controller.MESSAGE_TYPE[i].level+ " )";}}
  rslt+= rslt=="" ? " " : " )";
  //console.log('rslt', rslt);    
  return rslt;
}

dbutil.debug_controller.prototype.setStart = function(val){
    dbutil.database.setStart(val, this, dbutil.debug_controller.MIN_PERIOD, dbutil.debug_controller.MAX_PERIOD);
}

dbutil.debug_controller.prototype.setStop = function(val){
    dbutil.database.setStop(val, this, dbutil.debug_controller.MIN_PERIOD, dbutil.debug_controller.HOUR_PERIOD, dbutil.debug_controller.MAX_PERIOD);
}


dbutil.debug_controller.prototype.setLastHour = function(){
    dbutil.database.setNow(this, dbutil.debug_controller.HOUR_PERIOD);;
    this.run();
}

dbutil.debug_controller.prototype.setLastDay = function(){
    dbutil.database.setNow(this, dbutil.debug_controller.DAY_PERIOD);;
    this.run();
}

dbutil.debug_controller.prototype.setNow = function(){
    dbutil.database.setNow(this);;
    this.run();
}

dbutil.debug_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

dbutil.debug_controller.prototype.updatedate = function(){
    if (this.stoppicker && this.stop)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker && this.start)
        this.startpicker.datetimepicker('setDate', (this.start));        
}

dbutil.debug_controller.prototype.setstate = function(){
    $( "#select-button" ).button((this.connection && this.checkitem && this.checkitem.length) ? "enable"  : "disable");
    $( "#allmessage-button" ).button((this.connection && this.checkitem && this.checkitem.length && this.checked != dbutil.debug_controller.MSG_FULL) ? "enable"  : "disable");
    $( "#nomessage-button" ).button((this.connection && this.checkitem && this.checkitem.length && this.checked) ? "enable"  : "disable");
    $( "#run-button" ).button((!this.requested && this.connection && this.checked) ? "enable"  : "disable");
    $( "#hour-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#day-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((!this.requested && this.connection) ? "enable"  : "disable");} 

dbutil.debug_controller.prototype.setselectpanel = function(val){
    var panel = $( "#select-panel-debug" )[0];
    panel.className = val ? 'ui-widget-content select-panel-visible' : 'ui-widget-content select-panel-hidden';
    panel.visibility = val ? true : false;   
}

dbutil.debug_controller.prototype.resetselectpanel = function(){
    var panel = $( "#select-panel-debug" )[0];
    this.setselectpanel(!panel.visibility);    
}







// report_controller
/*
    const tagtype  REPORTTYPE_YEAR             = 1  | TYPE_REPORT;
    const tagtype  REPORTTYPE_MIN              = 0x2  | TYPE_REPORT;
    const tagtype  REPORTTYPE_HOUR             = 0x3  | TYPE_REPORT;
    const tagtype  REPORTTYPE_DEC              = 0x4  | TYPE_REPORT;
    const tagtype  REPORTTYPE_DAY              = 0x5  | TYPE_REPORT;
    const tagtype  REPORTTYPE_MONTH            = 0x6  | TYPE_REPORT;
    const tagtype  REPORTTYPE_10MIN            = 0x7  | TYPE_REPORT;
    const tagtype  REPORTTYPE_30MIN            = 0x8  | TYPE_REPORT;
    const tagtype  REPORTTYPE_QVART            = 0x9  | TYPE_REPORT;
    const tagtype  REPORTTYPE_CUSTOM           = 0xA  | TYPE_REPORT;
    const tagtype  REPORTTYPE_NONE             = 0x0  | TYPE_REPORT;*/


  
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


dbutil.report_controller.REPORTTYPE_YEAR             = 1;
dbutil.report_controller.REPORTTYPE_MIN              = 2;
dbutil.report_controller.REPORTTYPE_HOUR             = 3;
dbutil.report_controller.REPORTTYPE_DEC              = 4;
dbutil.report_controller.REPORTTYPE_DAY              = 5;
dbutil.report_controller.REPORTTYPE_MONTH            = 6;
dbutil.report_controller.REPORTTYPE_10MIN            = 7;
dbutil.report_controller.REPORTTYPE_30MIN            = 8;
dbutil.report_controller.REPORTTYPE_QVART            = 9;

dbutil.report_controller.getStartReportTime = function(type, time){
    switch (type){
      case dbutil.report_controller.REPORTTYPE_YEAR:  {time.setMonth(0);time.setDate(1);time.setHours(0);time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_HOUR:  {time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_DEC:   {time.setDate( (time.getDate() < 11) ?  1 : (time.getDate() < 21 ? 11 : 21) );time.setHours(0);time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_DAY:   {time.setHours(0);time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_MONTH: {time.setDate(1);time.setHours(0);time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_10MIN: {var minute =parseInt(time.getMinutes()/10)*10;time.setMinutes(minute);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_30MIN: {var minute =parseInt(time.getMinutes()/30)*30;time.setMinutes(minute);time.setSeconds(0);time.setMilliseconds(0);return time;}
      case dbutil.report_controller.REPORTTYPE_QVART: {var month =time.getMonth();time.setMonth( month<7 ? (month<4 ? 1 : 4) : (month<10 ? 7 : 10));time.setDate(1);time.setMinutes(0);time.setSeconds(0);time.setMilliseconds(0);return time;}      
    }
    return null;
}

dbutil.report_controller.getStopReportTime = function(type, time){
    switch (type){
      case dbutil.report_controller.REPORTTYPE_YEAR:  {time.setFullYear(time.getFullYear()+1);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_HOUR:  {time.setHours(time.getHours()+1);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_DEC:   {if (time.getDate()>20) {time.setDate(1);time.setMonth(time.getMonth()+1);} else time.setDate(time.getDate()+10);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_DAY:   {time.setHours(time.getHours()+24);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_MONTH: {time.setMonth(time.getMonth()+1);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_10MIN: {time.setMinutes(time.getMinutes()+10);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_30MIN: {time.setMinutes(time.getMinutes()+30);time = dbutil.report_controller.getStartReportTime(type, time);return time;}
      case dbutil.report_controller.REPORTTYPE_QVART: {time.setMonth(time.getMonth()+3);time = dbutil.report_controller.getStartReportTime(type, time);return time;}      
    }
    return null;
}

dbutil.report_controller.incReportTime = function(type, time , cnt){
    if (!cnt) return time;
    switch (type){
      case dbutil.report_controller.REPORTTYPE_YEAR:  {time.setFullYear(time.getFullYear()+cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_HOUR:  {time.setHours(time.getHours()+cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_DEC:   {if (time.getDate()>20) {time.setDate(1);time.setMonth(time.getMonth()+1);} else time.setDate(time.getDate()+10);return time;}
      case dbutil.report_controller.REPORTTYPE_DAY:   {time.setHours(time.getDate()+cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_MONTH: {time.setMonth(time.getMonth()+1 * cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_10MIN: {time.setMinutes(time.getMinutes()+10 * cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_30MIN: {time.setMinutes(time.getMinutes()+30 * cnt);return time;}
      case dbutil.report_controller.REPORTTYPE_QVART: {time.setMonth(time.getMonth()+3 * cnt);return time;}      
    }
    return null;    
}

dbutil.report_controller.reportRange = function(type, time){
    return {start : dbutil.report_controller.getStartReportTime(type, new Date(time)), stop : dbutil.report_controller.getStopReportTime(type, new Date(time))};
}

dbutil.report_controller.reportRangeTest = function(type, time){
    return {start : dbutil.database.date(dbutil.report_controller.getStartReportTime(type, time)), stop : dbutil.database.date(dbutil.report_controller.getStopReportTime(type, time))};
}


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
        this.selected=null;
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
        //this.setStart(new Date((new Date()).valueOf() - dbutil.report_controller.MID_PERIOD));
        //this.setStop(new Date());        
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
    //if (!this.xml.length){
    //    dbutil.database.modal(dbutil.database.FATAL, dbutil.database.ERROR_WR_APPTRINFO  + dbutil.database.APPINFOFILE);
    //    return;
    //}
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
            var delt = el.getAttribute("delt") ? parseInt(el.getAttribute("delt"))  : 0;
            var group = el.getAttribute("group") ? parseInt(el.getAttribute("group")) : 1;
            var sum = el.getAttribute("sum") ? parseInt(el.getAttribute("sum")) : 1;
            var type = el.getAttribute("type") ? parseInt(el.getAttribute("type")) : 0;  
            var initperiod = el.getAttribute("initperiod") ? parseInt(el.getAttribute("initperiod")) : 0;
            var subperiod = el.getAttribute("subperiod") ? parseInt(el.getAttribute("subperiod")) : 0;            
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
        beforeSelectRow: function(){
            $("#list").jqGrid('resetSelection');
            return true;
        },
        onSelectRow: function (rowId, status, e) {
            var row = $("#list").jqGrid('getRowData',rowId);
            ts.select(status ? rowId : undefined);      
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
            width:1000
        }
        
    
		
        ],
        rowNum: 100000,
        //treeIcons: {plus:'ui-icon-circle-arrow-e',minus:'ui-icon-triangle-1-s',leaf:'ui-icon-radio-off'},
   	hidegrid: false,
        viewrecords: true,
        grouping:true,
        multiselect: true,
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



dbutil.report_controller.prototype.updatelist = function( req ) {
    $("#list").jqGrid('clearGridData');
    for (var i=0;i<this.xml.length;++i)
        this.xml[i].rowid=(i).toString();
        $("#list").jqGrid('addRowData',"rowid",this.xml);   
        $("#list").trigger("reloadGrid");
}


dbutil.report_controller.prototype.select = function(val){
    //console.log('rowid', val)
    this.selected = val ? this.xml[parseInt(val)] : undefined;
    if (this.selected)
        this.selectedtime = dbutil.report_controller.reportRange(this.selected.type , dbutil.report_controller.incReportTime(this.selected.type, new Date(), -this.selected.initperiod));
    if (this.selectedtime && this.selectedtime.start && this.selectedtime.stop){
        this.setStart(this.selectedtime.start);
        this.setStop(this.selectedtime.stop);        
        this.updatedate();        
    }
    else
        {
        this.selected = undefined;
        }
    this.showselect();
}    

dbutil.report_controller.prototype.showselect = function(){
    var header = this.selected  ? (this.selected.list + '. '+ this.selected.name) : 'Не выбрано.';
    header = header + ((this.selectedtime && this.selected)  ? (' c ' + dbutil.database.date(this.selectedtime.start) + ' по '+ dbutil.database.date(this.selectedtime.stop)) : '');
    if (document.getElementById('report-header')) 
        document.getElementById('report-header').textContent=header;
} 



dbutil.report_controller.prototype.run = function(){
    this.setselectpanel(false);
    dbutil.database.modal(dbutil.database.PROCCESS, dbutil.database.MESSAGE_DATAREQUEST );
    var ts = this;
    ts.requested=true;
    ts.setstate();   
}


dbutil.report_controller.prototype.setStart = function(val){
    this.start=val;
}

dbutil.report_controller.prototype.setStop = function(val){
    this.stop=val;
}

dbutil.report_controller.prototype.setLeft = function(){
    if (this.start && this.stop && this.selected){
        var tm= new Date( (this.start.valueOf() + this.stop.valueOf()) /2);
        this.selectedtime = dbutil.report_controller.reportRange(this.selected.type , dbutil.report_controller.incReportTime(this.selected.type, tm, -1));
        this.updatedate();
    }
}

dbutil.report_controller.prototype.setRight = function(){
    if (this.start && this.stop &&  this.selected && (this.stop < new Date())){
        var tm= new Date( (this.start.valueOf() + this.stop.valueOf()) /2);
        this.selectedtime = dbutil.report_controller.reportRange(this.selected.type , dbutil.report_controller.incReportTime(this.selected.type, tm, 1));
        this.updatedate();
    }
}

dbutil.report_controller.prototype.setNow = function(){
    if (this.start && this.stop &&  this.selected && (this.stop < new Date())){
        var tm= new Date();
        this.selectedtime = dbutil.report_controller.reportRange(this.selected.type , dbutil.report_controller.incReportTime(this.selected.type, tm, 1));
        this.updatedate();
    }
}

dbutil.report_controller.prototype.normalizePeriod = function(){
    this.updatedate();
    this.requested=false;
    this.setstate();
}

dbutil.report_controller.prototype.updatedate = function(){
    if (this.stoppicker)
        this.stoppicker.datetimepicker('setDate', (this.stop));
    if (this.startpicker)
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
    $( "#run-button" ).button((this.selected && this.start && this.stop && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#left-button" ).button((this.selected && this.start && this.stop  && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#right-button" ).button((this.selected && this.start && this.stop  && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#now-button" ).button((this.selected && this.start && this.stop && !this.requested && this.connection) ? "enable"  : "disable");    
    $( "#select-button" ).button((this.xml.length) ? "enable"  : "disable");
    $( "#noparam-button" ).button((this.items.length && !this.requested && this.connection) ? "enable"  : "disable");
    $( "#print-button" ).button((false) ? "enable"  : "disable");
    if (!this.selected && this.xml.length)
        this.setselectpanel(true);
}
