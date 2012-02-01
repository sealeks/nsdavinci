function motor_btn_click(ev){
    var el=ev.target;
    //var cmd=ev+" @ 1";
    //dvnci_exec(cmd);
    if (el.getAttribute('class')=='on_button size_80pst')
        el.setAttribute('class', 'off_button size_80pst');
    else
        el.setAttribute('class', 'on_button size_80pst');
    ev.stopPropagation();
}

function motor_b_click(ev, tag, desc){
      var tgnm=ev;
      var idtgnm=ev + '_divelem';
      var newwin = open('', 'jjjj', "toolbar=0,location=0,left=400,top=200, width=250,height=250");
      newwin.document.open();    
      newwin.document.write('<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">'+
                            '<html xmlns="http://www.w3.org/1999/xhtml" style="background-image: url(&_quot;../mainlib/css/res/bgrd2.png&_quot;); margin: 0 0; padding: 0 0; width: 100%; height: 100%;">'+
                            '<head><link rel="stylesheet" type="text/css" href="../mainlib/css/mainstyle.css"/><script type="text/javascript">\n'+                           
                            'function motor_btn_click(ev)\n{var el=ev.target;\nvar cmd='+
                            "'" +tag + "'"+
                            '+" @ 1";\nif (el.getAttribute('+"'"+'class'+"'"+')=='+"'"+'off_button size_80pst'+"'"+')\n{cmd='+
                            "'" +tag + "'"+
                            '+" @ 0";} \ndvnci_exec(cmd);\nev.stopPropagation();} \n\nfunction init(){ var el = document.getElementById("btn");'+
                            'el.setAttribute("class", "#{ '+
                            tag+
                            ' ? '+"'"+ "off_button size_80pst" + "'"+' : ' + "'" + 'on_button size_80pst' + "'"+ '}");'+
                            '}</script></head><body style="margin: 0 0; padding: 0 0; width: 100%; height: 100%; " onload="init()">'+
                            '<div  style="width: 100%; height: 100%; "><table class="ccc_panel_bottom"><tbody><tr><th  class="firebrick_panel_top midle_header">'+           
                            (desc ? desc : tag ) +
                            '</th> </tr> <tr><td class="size_100pst"><button id="btn" onclick="motor_btn_click(event)" >'+
                            '#{ ' +tag +  " ? '"+'Off'+"' : '"+'On'+"'"+'}</button></td></tr></tbody></table> </div></body></html>');
      newwin.document.close();}

            
            
function check_is_parent(el, self){
    var tst=el;
    if ((!tst) || (tst==document.documentElement)) return false;
    while (tst.parentNode!=document.documentElement){
        if (tst.parentNode==self){
            return true;
        }
        tst=tst.parentNode;
    }
    return false;
}
            
function motor_click(ev, ths, nm){
    var targelem=ev.target;                
    var elem_x0=targelem.offsetLeft + targelem.offsetWidth / 2;
    var elem_y0=targelem.offsetTop+targelem.offsetHeight / 2;
    var popup_height=targelem.offsetHeight + 8;
    var popup_width=200;
    var popup_x0= elem_x0 - popup_width / 2;
    var popup_y0=elem_y0 - popup_height / 2;
                
    var div  = document.createElement('div');
    div.setAttribute('class', 'fixed_80opacity');
    div.setAttribute('style', 'top: '+popup_y0+'px; left: '+popup_x0+'px; width: '+popup_width+'px; height: '+150+'px;');
    div.onclick=function(evt){
        if (evt) evt.stopPropagation()
            };
                
    var table = document.createElement('table');
    table.setAttribute('class', 'ccc_panel_bottom');


                
                
    var caption = document.createElement('caption');
    caption.setAttribute('style', 'height: '+ popup_height +'px');
                

                
                
    var tbody = document.createElement('tbody');
                
    var tr1 = document.createElement('tr');
                
    var th = document.createElement('th');
    th.setAttribute('class', 'firebrick_panel_top midle_header');
    th.innerHTML=nm;               
                
    var tr2 = document.createElement('tr');
                
    var td = document.createElement('td');
    td.setAttribute('class', 'size_100pst');
                
    var btn = document.createElement('button');
    btn.setAttribute('class', 'on_button size_80pst');
    btn.onclick=function(){
        return motor_btn_click(event);
    }
    btn.innerHTML="Включить"; 
                
    td.appendChild(btn);
    tr2.appendChild(td);
                
    tr1.appendChild(th);
                
    tbody.appendChild(tr1);
    tbody.appendChild(tr2);
                
    table.appendChild(caption);
    table.appendChild(tbody);
                
    div.appendChild(table);
                
    targelem.appendChild(div);
                
    table.onmouseout=function(event){
        if ((event.target!=table) &&
            (event.relatedTarget!=table) && 
            (check_is_parent(event.target, table)) && 
            (!check_is_parent(event.relatedTarget, table)))
            targelem.removeChild(div);
    }                  
}

