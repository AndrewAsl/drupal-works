<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
    Раздел по квадрату
 */
function calcmet_polosa_form($form, &$form_state){
    $form = array();
    $form['polosa'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#prefix' => '<div id="menu-zone"></div>',
        //'#suffix' =>'</div>'  
    );
    
    $form['polosa']['options'] = array(
        '#title' => t('Полоса толщина х ширина'),
        '#type' => 'select',
        '#options' => calcmet_get_options('calcmetpolosa'),
        '#default_value' => 1,
        '#size' => 10,
        '#description' => t('Выберите тип полосы'),
        /*'#ajax' => array(
            'wrapper' => '',
            'callback' => 'polosa_change_info',
        ),*/
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'  
    );
    $form['polosa']['length'] = array(
        '#title' => t('Длина, м'),
        '#type' => 'textfield',
        '#size' => 20,
        '#description' => t('Введите длину в метрах, м'),
        '#element_validate' => array('element_validate_number'),
//        '#ajax' => array(
//            'wrapper' => '',
//            'callback' => 'polosa_calculate_result',
//        ),
        '#prefix' => '<div class = "col-md-4">',
    );
    $form['polosa']['mass'] = array(
       '#title' => t('Расчитанная масса, кг'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="masscalcul"></div>',
       //'#suffix' =>'</div>'
    );
    $form['polosa']['csadraw'] = array(
       '#title' => t('Расчитанная площадь окраски с одной стороны, м2'),
       '#type' => 'item',
       '#markup' => '<div style="border: 1px solid #ccc; width: 200px; height: 35px" id="csadraw"></div>',
       '#suffix' =>'</div>'
    );
    $form['polosa']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="/sites/default/files/image/polosa.jpg" width=200px></div>',
        '#prefix' => '<div class = "col-md-4">',
        '#suffix' =>'</div>'
    );
    
    $form['polosa']['info'] = array(
       '#type' => 'item',
       '#markup' => '<div id="polosa-info">'
        . '<strong>Ширина полосы, мм:</strong> <span id="width">12</span><br>'
        . '<strong>Толщина полосы, мм:</strong> <span id="thick">4</span><br>'
        . '<strong>Масса 1 м, кг:</strong> <span id="massonem">0.377</span><br>'
        . '<strong>Норматив:</strong> ГОСТ 103-2006 "Прокат сортовой стальной горячекатаный полосовой. '
        . 'Сортамент" утвержден постановлением Госстандарта Республики Беларусь от 30.01.2007 № 4',
        '#prefix' => '<div class = "col-md-8">',
        '#suffix' =>'</div>',        
    );
    $form['specbutton'] = array(
       '#type' => 'submit',
       '#value' => t('Добавить в спецификацию'),
       '#prefix' => '<div class = "col-md-4" id="btnspec"> ',
       '#suffix' =>'</div>',        
    );
    
    $form['polosa']['spec'] = array(
        '#type' => 'item',
        '#markup' => '<div class="col-md-9"> Спецификация</div>'
        .'<div class="col-md-3"><span class="glyphicon glyphicon-print"></span></div>'
        .'<div><table id="spec" class="table"><tbody>'
        . '<tr>'
        . '<th>№ п/п</th>'
        . '<th>Название</th>'
        . '<th>Длина, м</th>'
        . '<th>Масса, кг</th>'
        . '<th>Площадь окраски, м2</th>'
        . '<th></th>'
        . '</tr>'
        . '</tbody>'
        . '</table></div> ',
        '#prefix' => '<div class = "col-md-12">',
        '#suffix' =>'</div>',
    );
    $form['#attached']['js'] = array(
        drupal_get_path('module', 'calcmet') . '/calcmetpolosa.js',
    );
    return $form;
}
/*
 * Конец формы для двутавра
 */

function polosa_change_info(){
    $select = $_POST['polosaselect'];
    //dsm($select);
    $infos = db_select('calcmetpolosa', 'p')
            ->fields('p', array('polwidth', 'polthikcness', 'polmassonem',))
            ->condition('p.pdid', $select)
            ->execute()
            ->fetchAll();
    $polwidth = $infos[0]->polwidth;
    $polthikcness = $infos[0]->polthikcness;
    $massonem = $infos[0]->polmassonem;
    drupal_json_output(array(
                        'polwidth' => $polwidth, 
                        'polthikcness' => $polthikcness, 
                        'massonem'=>$massonem,
                        
        ));
    drupal_exit();
}

function calcmet_get_options ($basename){
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    foreach ($entries as $entry) {
        switch ($basename) {
            case 'calcmetpolosa':
                $options[$entry->pdid] = $entry->polosaname;
                break;

            default:
                break;
        }
    }
    return $options;
}