
function dvn_onalarm_proc(evnt) {
    var el = document.getElementById("alarmtable");
    if (el==null) return;
    if (el.value=="") return;
    cleartable();
    fillrowtab(evnt);         
}
        
          
function cleartable() {
    var el = document.getElementById("alarmtable");
    if (el==null) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    while (el.children.length>1)
        el.removeChild(el.lastChild);
}
  
function fillrowtab(evnt){
    var el = document.getElementById("alarmtable");
    if ((el==null) || (evnt==null)) return;
    var tbel = el.getElementsByTagName("tbody");
    if (tbel.length==0) return;    
    el = tbel[0];
    for (var i=0;i<evnt.length;++i){
        insertrow(el, evnt[i]);
    }
     
}


function insertrow(el, arr) {

    if (el.children.length==0) return;
    var tr  = document.createElement('tr');
    if (arr[2]==0){
        tr.setAttribute("class", (arr[1]>2) ? "avaron" : ((arr[1]>1) ? "alarmon" : "noticeon"));
    }
    else{
        tr.setAttribute("class", (arr[1]>2) ? "avarkvit" : ((arr[1]>1) ? "alarmkvit" : "noticekvit"));
    }

      
    for (var i=0; i<arr.length-1 ;++i){
        if ((i==0) || (i>2)){
            td = document.createElement('td');
            if (i==0){
                var tm= new Date(0,0,0, arr[i].getHours() ,arr[i].getMinutes() 
                    +arr[i].getTimezoneOffset(),arr[i].getSeconds());
                var ta = document.createTextNode(tm.toLocaleTimeString());
                var sp = document.createElement('span');
                sp.setAttribute("class", "smallfont");
                sp.appendChild(ta);
                td.appendChild(sp);
                tr.appendChild(td);
            }
            else{
                var ta = document.createTextNode(arr[i]);
                var sp = document.createElement('span');
                sp.setAttribute("class", "smallfont");
                sp.appendChild(ta);
                td.appendChild(sp);
                tr.appendChild(td);
            }
        }
    }
      
el.appendChild(tr);
}
        
function kvit(){
    dvnci_exec("#");
}

