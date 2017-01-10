/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetArmatura = {
        'attach': function(context, settings) {
            /*$(document, context).keypress(function(e){
                //var keycode = (e.keyCode ? e.keyCode : e.which);
                if(e.keyCode == '13'){
                    //e.stopPropagation();
                    //e.preventDefault();
                    alert ('Нельзя нажимать ввод');
                    return false;
                }                
            });*/
            var diametr = $('select#edit-armatura-options');
            //console.log(diametr);
            var url = Drupal.settings.basePath + 'services/calcmet/armatura/armatura_change_info';
            var dlina = $('input#edit-armatura-length');
            var mass = $('span#massonem');
            //var diametr = $('select#edit-armatura-options');
            
            var diamsel;
            
            //console.log(dlina, diametr);
            diametr.on('change', function(){                
                $('select#edit-armatura-options option:selected').each(
                    function(){
                        diamsel = $(this).val();
                        //console.log(diamsel);
                        $.post(url, {'armaturaselect' : diamsel}, function(data){
                            $('span#csa').text(data.csa);
                            $('span#massonem').text(data.massonem);
                            if(! parseFloat(dlina.val()) )
                                //console.log(typeof(dlina.val()));
                                return;
                            $result = dlina.val()*data.massonem;
                            $('div#masscalcul').text($result);
                            //console.log(data.csa, data.massonem);
                        });
                    }
                );                
            });
            dlina.on('change', function() {
                var number = parseFloat(dlina.val());
                //console.log (number);
                if (!number){
                    alert ('Длина должна быть числом');
                    return;
                }
                $result = $(this).val()*mass.text();
                $('div#masscalcul').text($result);
                //return false;
            });
            dlina.keypress(function(e){
                if (e.keyCode === 13){
                    e.preventDefault();
                    //return false;
                    var number = parseFloat(dlina.val());
                //console.log (number);
                if (!number){
                    alert ('Длина должна быть числом');
                    return;
                }
                $result = $(this).val()*mass.text();
                $('div#masscalcul').text($result);
                }
            });
            //});
            //return false;
        var btntospec = $('button#edit-specbutton');
        btntospec.on('click', function(e){
            e.preventDefault();
            var numpp = $('table#spec tr').length;
            var dintbl = $('select#edit-armatura-options option:selected').text();
            var dlinaintbl = dlina.val();
            var massintbl = $('div#masscalcul').text();
            var html = '<tr><td>'+ numpp +'</td>'
                        +'<td>Диаметр стержня: ' + dintbl + '</td>' 
                        +'<td>'+ dlinaintbl + '</td>' 
                        +'<td>'+massintbl+'</td>'
                        +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
            if (dintbl && dlinaintbl && massintbl){
                $('table#spec').append(html);
            } else {
                alert ('Заполните все данные');
            }
            var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>'
               if(!$('div#btncab').length) 
                $('#edit-armatura-spec').append(btn);
            //console.log(html);
            var delrow = $("table#spec .deleterow", context);
            delrow.on("click",function(e) {
                e.preventDefault();
                var tr = $(this).closest('tr');
                tr.fadeOut(400, function(){
                    tr.remove();
                });
              return false;
            });
            $('div#btncab button').one("click",function(e) {
               //e.preventDefault();
               alert ('Данные в личный кабинет отправлены' );
               return false;
            });
        });
        
            
    }    
  };         
})(jQuery);

