/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
(function($) {
    Drupal.behaviors.calcmetDvutavr = {
        'attach': function(context, settings) {
            var name = $('select#edit-polosa-options');
            //console.log(diametr);
            var url = Drupal.settings.basePath + 'services/calcmet/polosa/polosa_change_info';
            var dlina = $('input#edit-polosa-length');
            //var height = $('span#height');
            var width = $('span#width');
            console.log (width.text());
            var thickness = $('span#thick');
            //var polkathickness = $('span#polkathickness');
            //var csa = $('span#csa');
            var mass = $('span#massonem');
            //var diametr = $('select#edit-armatura-options');
            
            var diamsel;
            var drawonemetr = 0.42;
            
            //console.log(dlina, diametr);
            name.on('change', function(){                
                $('select#edit-polosa-options option:selected').each(
                    function(){
                        diamsel = $(this).val();
                        //console.log(diamsel);
                        $.post(url, {'polosaselect' : diamsel}, function(data){
                            width.text(data.polwidth);
                            thickness.text(data.polthikcness);
                            mass.text(data.massonem);
                            if(! parseFloat(dlina.val()) )
                                //console.log(typeof(dlina.val()));
                                return;
                            $resultmassa = (dlina.val()*mass.text()).toFixed(3);
                            $resultcsadraw = (dlina.val()*0.001*data.polwidth).toFixed(3);
                            $('div#masscalcul').text($resultmassa);
                            $('div#csadraw').text($resultcsadraw);
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
                $resultmassa = ($(this).val()* mass.text()).toFixed(3);
                $resultcsadraw = ($(this).val()*0.001*width.text()).toFixed(3);
                $('div#masscalcul').text($resultmassa);
                $('div#csadraw').text($resultcsadraw);
                //return false;
            });
            dlina.keypress(function(e){
                if (e.keyCode === 13){
                    e.preventDefault();
                $resultmassa = ($(this).val()* mass.text()).toFixed(3);
                $resultcsadraw = ($(this).val()*0.001*width.text()).toFixed(3);
                $('div#masscalcul').text($resultmassa);
                $('div#csadraw').text($resultcsadraw);
                return false;
                }
            });
            //});
            //return false;
        var btntospec = $('button#edit-specbutton');
        btntospec.on('click', function(e){
            e.preventDefault();
            var numpp = $('table#spec tr').length;
            var dintbl = $('select#edit-polosa-options option:selected').text();
            var dlinaintbl = dlina.val();
            var massintbl = $('div#masscalcul').text();
            var csadraw = $('div#csadraw').text();
            var html = '<tr><td>'+ numpp +'</td>'
                        +'<td>' + dintbl + '</td>' 
                        +'<td>'+ dlinaintbl + '</td>' 
                        +'<td>'+massintbl+'</td>'
                        +'<td>'+csadraw+'</td>'
                        +'<td><span class="glyphicon glyphicon-remove-circle deleterow"></span></td></tr>';
            if (dintbl && dlinaintbl && massintbl && csadraw){
                $('table#spec').append(html);
            } else {
                alert ('Заполните все данные');
            }
            var btn = '<div id="btncab" class="col-md-offset-6 col-md-6"> <button class="btn btn-success" type="submit">Добавить в личный кабинет</button></div>'
               if(!$('div#btncab').length) 
                $('#edit-polosa-spec').append(btn);
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

