/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetSteel = {
        'attach': function(context, settings) {
        
            var csa = 0.0628;
            
            /*var SetCsa = function(){
                var form = $('form[id^="calcmet-tube"]');
                //console.log(form);
                if (form[0].id == 'calcmet-tube-bezshov-form'){
                    csa = 0.0628;
                    
                }
                if (form[0].id == 'calcmet-tube-form'){
                    csa = 0.0377;
                    
                }
                if (form[0].id == 'calcmet_tube_kvadrat_form'){
                    csa = 0.04;
                    
                }
                if (form[0].id == 'calcmet_tube_oval_form'){
                    csa = 0.0141;
                   
                }
                if (form[0].id == 'calcmet_tube_ugol_form'){
                    csa = 0.0000;
                    
                }
                console.log(csa);
                return csa;
            };*/

            var PreventEnter = function(){    
                $('input#edit-tube-length').keypress( function(e){
                    if (e.keyCode === 13){                        
                            var mass = $(this).val() * $('span#massonem').text();
                            var csadraw = $(this).val() * csa;
                            $('div#masscalcul').text(mass);
                            $('div#csadraw').text(csadraw);
                            e.preventDefault();
                        }                        
                    }
                );
            };
            
            var CalculateAndPlace = function (){
                $('input#edit-tube-length').change(function(){
                        var mass = $(this).val() * $('span#massonem').text();
                        var csadraw = $(this).val() * csa;
                        $('div#masscalcul').text(mass);
                        $('div#csadraw').text(csadraw);
                    });
            };
            
            var GetInfo = function(basename, value){
                //csa = SetCsa();
                value.each(function(){
                  $.post('/services/calcmet/tube/tube_change_info', 
                  {'tubename': basename, 'option': value.val()}, 
                  function(data){
                      
                        $('span#diametr').text(data.diametr);
                        $('span#razmer1').text(data.storona1);
                        $('span#razmer2').text(data.storona2);
                        $('span#thickness').text(data.thick);
                        $('span#massonem').text(data.massonem);
                        $('span#csa').text(data.csatext);
                        csa = data.csa;
                        console.log(csa);
                        if($('input#edit-tube-length').val()){
                          var mass = $('input#edit-tube-length').val() * data.massonem;  
                          var csadraw = $('input#edit-tube-length').val() * csa;  
                          $('div#masscalcul').text(mass);
                          $('div#csadraw').text(csadraw);
                        } else {
                           $('div#masscalcul').text(''); 
                           $('div#csadraw').text(''); 
                        }                      
                  });
              });
            };
            
            var ChangeOptions = function(){
                var name = $('select[id^="edit-tube"]');
                name.on('change', function(){
                    if (name[0].id === 'edit-tube-shovnames'){                  
                        GetInfo('shov', $('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();
                        
                    } else if (name[0].id === 'edit-tube-bezshvov'){
                        GetInfo('bezshvov',$('select#'+ name[0].id +' option:selected'));
                        PreventEnter();
                        CalculateAndPlace();
                       
                    } else if (name[0].id === 'edit-tube-kvnames'){
                       GetInfo('tubekvadrat', $('select#'+ name[0].id +' option:selected'));
                       PreventEnter();
                       CalculateAndPlace();
                       
                    } else if (name[0].id === 'edit-tube-ovalnames'){
                       GetInfo('tubeoval', $('select#'+ name[0].id +' option:selected'));
                       PreventEnter();
                       CalculateAndPlace();                       
                    } else if (name[0].id === 'edit-tube-ugolnames'){
                       GetInfo('tubeugol', $('select#'+ name[0].id +' option:selected'));
                       PreventEnter();
                       CalculateAndPlace();                       
                    }                   
                    else {
                        return;
                    }
                });
            };
            
            var AddToSpec = function(){
                var btntospec = $('#btnspec button');
                btntospec.on('click', function(e){
                    e.preventDefault();
                    //alert ('click');
                    var cat = $('select#edit-cat option:selected').text();
                    var numpp = $('table#spec tr').length;
                    var title, dlinaintbl, massintbl, csadraw, html;
                        title = 'Трубы ' + cat.toLowerCase()+' '+ $('select[id^=edit-tube] option:selected').text();
                        dlinaintbl = $('#edit-tube-length').val();
                        massintbl = $('#masscalcul').text();
                        csadraw = $('#csadraw').text();
                        if (title && dlinaintbl && massintbl && csadraw){
                            html = '<tr><td>'+ numpp +'</td>'
                                +'<td>' + title + '</td>' 
                                +'<td>'+ dlinaintbl + '</td>' 
                                +'<td>'+massintbl+'</td>'
                                +'<td>'+csadraw+'</td>'
                                +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
                            $('table#spec').append(html);
                        } else {
                            alert ('Необходимо заполнить все данные');
                            return false;
                        }                                           
                    var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>';
                       if(!$('div#btncab').length) 
                        $('#edit-spec').append(btn);
                    //console.log(html);
                    var delrow = $("table#spec .deleterow", context);
                    delrow.on("click",function(e) {
                        e.preventDefault();
                        var tr = $(this).closest('tr');
                        tr.fadeOut(400, function(){
                            tr.remove();
                            if ($('table#spec tr').length === 1){
                                $('div#btncab').remove();
                            }
                        });
                      return false;
                    });
                    $('div#btncab button').one("click",function(e) {
                       //e.preventDefault();
                       alert ('Данные в личный кабинет отправлены' );
                       return false;
                    });
                });
            };
            
            $('select#edit-cat', context).on('change', function(e){
                e.stopPropagation();
                var txtForCsa = $('select#edit-cat option:selected').text();
                //console.log (txtForCsa);
                switch (txtForCsa){
                    case 'стальные бесшовные горячедеформированные':
                        csa = 0.0628;
                    break;    
                    case 'стальные электросварные прямошовные':
                        csa = 0.0377;
                    break;    
                    case 'стальные квадратные':
                        csa = 0.04;
                    break;    
                    case 'стальные овальные':
                        csa = 0.01413;
                    break;    
                    case 'стальные прямоугольные':
                        csa = 0.05;
                    break;
                    //console.log(csa);
                }
                $('select#edit-cat option:selected').each(
                    function(){  
                      $.post('/services/calcmet/tube/tube_change_options', {'ajaxtubechangeoptions': $(this).val()}, function(data){
                          $('section#block-system-main form[id^="calcmet-tube"]').replaceWith(data);
                      })
                      .always(function(){ ChangeOptions(); CalculateAndPlace(); PreventEnter(); AddToSpec(); });  
                    }                                    
                );
                
            });     
            
            //SetCsa();
            CalculateAndPlace();
            PreventEnter();
            ChangeOptions();
            AddToSpec();
        }       
  };         
})(jQuery);

